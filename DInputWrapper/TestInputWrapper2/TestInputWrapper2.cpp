// TestInputWrapper2.cpp : アプリケーションのエントリ ポイントを定義します。
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
			dipdw.dwData            = 8; // バッファのサイズ

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

// グローバル変数:
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
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

 	// TODO: ここにコードを挿入してください。
	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTINPUTWRAPPER2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTINPUTWRAPPER2));

	// メイン メッセージ ループ:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//描画領域の更新
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
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
//  コメント:
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//    Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
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
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

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




// テキストの描画
VOID PaintText(HWND hWnd)
{
	HDC hdc;
	PAINTSTRUCT ps;
	//BYTE    diks[256];   // キーボードの状態
	TCHAR buf[1024];

	// キーボードのキー取得
	//ckey->GetKey(sizeof(diks), diks);
	keyboard kbd;
	if (!im.update(kbd)) {
		output("Failed to retrieve keyboard state.\n");
	}

	hdc = BeginPaint (hWnd, &ps);
	// TODO: この位置に描画用のコードを追加してください...
	RECT rt;
	GetClientRect( hWnd, &rt );

	/*---指定したキーの入力があるか判定する例---*/

	//上
	if(kbd.pressed(DIK_UP))
	{
		wsprintf( buf, TEXT("UP"));
		DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );
		rt.left += 48;
		rt.right = rt.left + 64;
	}

	//下
	if(kbd.pressed(DIK_DOWN))
	{
		wsprintf( buf, TEXT("DOWN"));
		DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );

		rt.left += 48;
		rt.right = rt.left + 64;
	}

	//左
	if(kbd.pressed(DIK_LEFT))
	{
		wsprintf( buf, TEXT("LEFT"));
		DrawText( hdc, buf, strlen(buf), &rt, DT_LEFT );

		rt.left += 48;
		rt.right = rt.left + 64;
	}

	//右
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

	/*---全キーをチェックして押されたキーコードを返す例---*/

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
				// 改行
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
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
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
		// 選択されたメニューの解析:
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
		// TODO: 描画コードをここに追加してください...
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

// バージョン情報ボックスのメッセージ ハンドラーです。
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
