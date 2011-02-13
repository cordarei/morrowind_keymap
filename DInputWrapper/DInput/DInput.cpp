/**
 * File: DInput.h
 * Author: Joseph I.
 *
 * Defines the hook function to get our
 * DInput device wrapper.
 */

#include "stdafx.h"
#include "DInput.h"

/// Function signature for the wrapper function
typedef HRESULT (WINAPI *MYPROC )(HINSTANCE,DWORD,REFIID,void**,void*);

/**
 * \function DoDirectInput8Create
 * \brief Wraps a normal DInput device with our wrapper class.
 *
 * Loads "DInputWrapper.dll" and calls its version of \code DirectInput8Create ,
 * which creates our wrapper device and returns it.
 *
 * Should we cache the handle? Free library somewhere (where)?
 */
DINPUT_API HRESULT WINAPI DoDirectInput8Create(
	HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID *ppvOut,
    LPUNKNOWN punkOuter
) {
	HMODULE FakeD3Ddll=LoadLibraryW(WRAPPER_DLL_PATH);
    MYPROC func=(MYPROC)GetProcAddress(FakeD3Ddll, "DirectInput8Create");
	if (0 == func) return E_HANDLE;
    return (func)(hinst,dwVersion,riidltf,ppvOut,punkOuter);
}

//DINPUT_API HRESULT _stdcall DirectInput8Create(HINSTANCE a,DWORD b,REFIID c,void** d,void* e) {
//    HMODULE FakeD3Ddll=LoadLibrary("DInputWrapper.dll");
//    MYPROC func=(MYPROC)GetProcAddress(FakeD3Ddll,"DirectInput8Create");
//	if (0 == func) return E_HANDLE;
//    return (func)(a,b,c,d,e);
//}