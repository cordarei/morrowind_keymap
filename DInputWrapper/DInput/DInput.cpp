// DInput.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "DInput.h"

typedef HRESULT (WINAPI *MYPROC )(HINSTANCE,DWORD,REFIID,void**,void*);

DINPUT_API HRESULT WINAPI DoDirectInput8Create(
	HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID *ppvOut,
    LPUNKNOWN punkOuter
) {
	HMODULE FakeD3Ddll=LoadLibrary("DInputWrapper.dll");
    MYPROC func=(MYPROC)GetProcAddress(FakeD3Ddll,"DirectInput8Create");
	if (0 == func) return E_HANDLE;
    return (func)(hinst,dwVersion,riidltf,ppvOut,punkOuter);
}

//DINPUT_API HRESULT _stdcall DirectInput8Create(HINSTANCE a,DWORD b,REFIID c,void** d,void* e) {
//    HMODULE FakeD3Ddll=LoadLibrary("DInputWrapper.dll");
//    MYPROC func=(MYPROC)GetProcAddress(FakeD3Ddll,"DirectInput8Create");
//	if (0 == func) return E_HANDLE;
//    return (func)(a,b,c,d,e);
//}