// TestInputWrapper2.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "dinput.h"
#include "TestInputWrapper2.h"

#include "keyboard.h"
#include "com_ptr.h"


class input_mgr {
public:
	input_mgr() : _dinput(0), _device(0), _acq(false) {}
	~input_mgr() {
		unacquire();
	}

	bool init(HWND hwnd, HINSTANCE hInst) {
		HRESULT hr = 0;

		{
			IDirectInput8* ptr;
			hr = ::DirectInput8Create(
				hInst, 
				DIRECTINPUT_VERSION, 
				IID_IDirectInput8, 
				reinterpret_cast<void**>(&ptr), 
				0);
			if (FAILED(hr)) {
				output("Failed to create DInput8 handle.\n");
				return false;
			}

			_dinput = com_ptr<IDirectInput8>(ptr);
		}

		{
			IDirectInputDevice8* ptr;
			hr = _dinput->CreateDevice(GUID_SysKeyboard, &ptr, 0);
			if (FAILED(hr)) {
				output("Failed to create keyboard device.\n");
				return false;
			}

			_device = com_ptr<IDirectInputDevice8>(ptr);
		}

		hr = _device->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) {
			output("Failed to set device data format.\n");
			return false;
		}

		hr = _device->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) {
			output("Failed to set device cooperative level.\n");
			return false;
		}

		{
			DIPROPDWORD dipdw = {0};
			dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			dipdw.diph.dwObj        = 0;
			dipdw.diph.dwHow        = DIPH_DEVICE;
			dipdw.dwData            = 8; // �o�b�t�@�̃T�C�Y

			hr = _device->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
			if (FAILED(hr)) {
				output("Failed to set device buffer size property.\n");
				return false;
			}
		}
		return true;
	}

	bool acquire() {
		if (!_acq) {
			HRESULT hr = _device->Acquire();
			_acq = !FAILED(hr);
			if (FAILED(hr)) {
				output("Failed to acquire device.\n");
			}
		}
		return _acq;
	}
	bool unacquire() {
		if (_acq) {
			HRESULT hr = _device->Unacquire();
			_acq = FAILED(hr);
		}
		return !_acq;
	}

	bool update(keyboard & kbd) {
		HRESULT hr = _device->GetDeviceState(KeyboardSize, kbd.data());
		return !FAILED(hr);
	}

private:
	com_ptr<IDirectInput8A> _dinput;
	com_ptr<IDirectInputDevice8A> _device;
	bool _acq;
};

input_mgr im;
HWND g_hwnd = 0;

#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �����ɃR�[�h��}�����Ă��������B
	MSG msg;
	HACCEL hAccelTable;

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTINPUTWRAPPER2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTINPUTWRAPPER2));

	// ���C�� ���b�Z�[�W ���[�v:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//�`��̈�̍X�V
		/*RECT rt;
		GetClientRect(msg.hwnd, &rt);
		InvalidateRect(msg.hwnd, &rt, TRUE);*/

		//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
//  �R�����g:
//
//    ���̊֐�����юg�����́A'RegisterClassEx' �֐����ǉ����ꂽ
//    Windows 95 ���O�� Win32 �V�X�e���ƌ݊�������ꍇ�ɂ̂ݕK�v�ł��B
//    �A�v���P�[�V�������A�֘A�t����ꂽ
//    �������`���̏������A�C�R�����擾�ł���悤�ɂ���ɂ́A
//    ���̊֐����Ăяo���Ă��������B
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTINPUTWRAPPER2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTINPUTWRAPPER2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hwnd = hWnd;

   /*if (!im.init(g_hwnd))
		return FALSE;*/

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




// �e�L�X�g�̕`��
VOID PaintText(HWND hWnd)
{
	HDC hdc;
	PAINTSTRUCT ps;
	//BYTE    diks[256];   // �L�[�{�[�h�̏��
	TCHAR buf[1024];

	// �L�[�{�[�h�̃L�[�擾
	//ckey->GetKey(sizeof(diks), diks);
	keyboard kbd;
	if (!im.update(kbd)) {
		output("Failed to retrieve keyboard state.\n");
	}

	hdc = BeginPaint (hWnd, &ps);
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������...
	RECT rt;
	GetClientRect( hWnd, &rt );

	/*---�w�肵���L�[�̓��͂����邩���肷���---*/

	//��
	if(kbd.pressed(DIK_UP))
	{
		wsprintf( buf, TEXT("UP"));
		DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );
		rt.left += 48;
		rt.right = rt.left + 64;
	}

	//��
	if(kbd.pressed(DIK_DOWN))
	{
		wsprintf( buf, TEXT("DOWN"));
		DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );

		rt.left += 48;
		rt.right = rt.left + 64;
	}

	//��
	if(kbd.pressed(DIK_LEFT))
	{
		wsprintf( buf, TEXT("LEFT"));
		DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );

		rt.left += 48;
		rt.right = rt.left + 64;
	}

	//�E
	if(kbd.pressed(DIK_RIGHT))
	{
		wsprintf( buf, TEXT("RIGHT"));
		DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );

		rt.left += 48;
		rt.right = rt.left + 64;
	}

	GetClientRect( hWnd, &rt );
	const int iRightMax = rt.right;

	rt.top+=32;

	/*---�S�L�[���`�F�b�N���ĉ����ꂽ�L�[�R�[�h��Ԃ���---*/

	for(int i=0; i < 256; i++)
	{
		if( kbd.pressed(static_cast<byte_t>(i)) )
		{
			sprintf( buf, TEXT("0x%02x "), i );
			DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );

			if(rt.left+64 <= iRightMax )
			{
				rt.left+=64;
				rt.right = rt.left + 64;
			}
			else
			{
				// ���s
				rt.top+=32;
				rt.left+=0;
				rt.right = rt.left + 64;
			}
		}

	}

	EndPaint( hWnd, &ps );

	if (kbd.pressed(EscapeKey))
		::DestroyWindow(hWnd);
}



//
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:  ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		if (!im.init(hWnd, hInst)) {
			::DestroyWindow(hWnd);
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		//hdc = BeginPaint(hWnd, &ps);
		// TODO: �`��R�[�h�������ɒǉ����Ă�������...
		im.acquire();
		PaintText(hWnd);
		//EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		//::RedrawWindow(hWnd, 0, 0, 0);
		{
			RECT rt;
			GetClientRect(hWnd, &rt);
			InvalidateRect(hWnd, &rt, TRUE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
