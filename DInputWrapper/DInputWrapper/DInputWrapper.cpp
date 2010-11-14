// DInputWrapper.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "DInputWrapper.h"

//definitions
typedef HRESULT (_stdcall *DInputProc)(HINSTANCE,DWORD,REFIID,LPVOID,LPUNKNOWN);
void* CreateInputWrapper(void* real);

DINPUTWRAPPER_API HRESULT _stdcall DoDirectInput8Create(HINSTANCE a, DWORD b, REFIID c, void ** d, void * e) {
	void * ret = 0;

	HMODULE dinput8dll = NULL;	//Handle to the real dinput dll
	DInputProc func = NULL;		//Handle to the real create dinput8 function

	char Path [MAX_PATH];
	
	GetSystemDirectoryA (Path, MAX_PATH);
	strcat_s (Path, 256, "\\dinput8.dll");
	
	dinput8dll = ::LoadLibraryA (Path);
	func = (DInputProc) GetProcAddress (dinput8dll, "DirectInput8Create");
	if (0 == func) return E_FAIL;
	
	HRESULT hr = (func) (a, b, c, &ret, reinterpret_cast<LPUNKNOWN>(e));
	if (hr != S_OK) return hr;

	*d = CreateInputWrapper (ret);
	return S_OK;
}

