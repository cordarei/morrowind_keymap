// TestInputWrapper.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "dinput.h"

#include "com_ptr.h"
#include "keyboard.h"

#include <string>
#include <algorithm>
#include <iostream>

//forward declaration
HWND GetConsoleHwnd(void);

class acquire_device {
public:
	acquire_device(IDirectInputDevice8* d) : _d(d) {
		_d->Acquire();
	}
	virtual ~acquire_device() {
		_d->Unacquire();
	}
private:
	IDirectInputDevice8* _d;
};

void output(std::string const& s) {
	//::OutputDebugStringA(s.c_str());
	std::cout << s;
}

int _tmain(int argc, _TCHAR* argv[])
{
	com_ptr<IDirectInput8> input(0);
	com_ptr<IDirectInputDevice8> device(0);

	HRESULT hr = 0;

	{
		IDirectInput8* ptr;
		hr = ::DirectInput8Create(
			::GetModuleHandleA(NULL), 
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8, 
			reinterpret_cast<void**>(&ptr), 
			0);
		if (FAILED(hr)) {
			output("Failed to create DInput8 handle.\n");
			return 0;
		}

		input = com_ptr<IDirectInput8>(ptr);
	}

	{
		IDirectInputDevice8* ptr;
		hr = input->CreateDevice(GUID_SysKeyboard, &ptr, 0);
		if (FAILED(hr)) {
			output("Failed to create keyboard device.\n");
			return 0;
		}

		device = com_ptr<IDirectInputDevice8>(ptr);
	}

	hr = device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		output("Failed to set device data format.\n");
		return 0;
	}

	hr = device->SetCooperativeLevel(GetConsoleHwnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		output("Failed to set device cooperative level.\n");
		return 0;
	}

	{
		DIPROPDWORD dipdw = {0};
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		dipdw.dwData            = 8; // バッファのサイズ

		hr = device->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
		if (FAILED(hr)) {
			output("Failed to set device buffer size property.\n");
			return 0;
		}
	}

	
	acquire_device acq(device.get());

	keyboard kbd;

	while(!kbd.pressed(EscapeKey))
	{
		kbd.reset();
		HRESULT hr = device->GetDeviceState(KeyboardSize, kbd.data());
		if (FAILED(hr)) {
			std::cout << "Failed to get keyboard device state\n";
			break;
		}

		std::cout << std::hex;
		//for(byte_t i = 0; i != KeyboardSize; ++i) {
		byte_t i = 0;
		do {
			if (kbd.pressed(i))
				std::cout << static_cast<size_t>(i) << " ";
		} while(i != KeyboardSize-1);
		//}
		std::cout << std::endl;

		::Sleep(100);
	}

	return 0;
}


HWND GetConsoleHwnd(void)
{
	size_t const MY_BUFSIZE = 1024; // コンソール ウィンドウのタイトル用のバッファサイズ
	HWND hwndFound;         // 呼び出し側へ返される値
	char pszNewWindowTitle[MY_BUFSIZE];
	// 作成されるウィンドウのタイトルが入ります
	char pszOldWindowTitle[MY_BUFSIZE]; // 元のウィンドウタイトルが入ります

	// 現在のウィンドウタイトルを取得します

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

	// 独自に、ウィンドウの新規タイトルをフォーマットします

	wsprintf(pszNewWindowTitle,"%d/%d",
		GetTickCount(),
		GetCurrentProcessId());

	// 現在のウィンドウタイトルを変更します

	SetConsoleTitle(pszNewWindowTitle);

	// ウィンドウタイトルのアップデートを確実なものにさせます

	Sleep(40);

	// ウィンドウの新規タイトルを探しにいきます

	hwndFound=FindWindow(NULL, pszNewWindowTitle);

	// 元のウィンドウタイトルへ戻します

	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}