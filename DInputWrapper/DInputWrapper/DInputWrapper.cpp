/**
 * File: DInputWrapper.h
 * Author: Joseph I.
 *
 * Defines the function to get our
 * DInput device wrapper.
 */

#include "stdafx.h"
#include "DInputWrapper.h"

/////////////////////////////////////////////
//declarations

///Signature for the DInput function we're wrapping
typedef HRESULT (_stdcall *DInputProc)(HINSTANCE,DWORD,REFIID,LPVOID,LPUNKNOWN);

/**
 * \function CreateInputWrapper
 * \brief Wraps given DInput device with a wrapper device
 *
 * Should probably do something about using void pointers.
 *
 * \param real the real DInput device from dinput8.dll
 * \return the wrapper device
 */
void* CreateInputWrapper(void* real);


/////////////////////////////////////////////
//implementation

/**
 * \function GetDInputDllPath
 * \brief return path to the system dinput8.dll
 */
void GetDInputDllPath(wchar_t *buf, size_t size) {
	wchar_t const *dll_filename = L"\\dinput8.dll";
	GetSystemDirectoryW(buf, size);
	wcscat_s(buf, size, dll_filename);
}


/**
 * \function DoDirectInput8Create
 * \brief Wraps a normal DInput device with our wrapper class.
 *
 * Loads "dinput8.dll" from the system directory and creates the requested device,
 * then creates a wrapper device around it and returns the wrapper.
 *
 * Should we cache the handle? Free library somewhere (where)?
 */
DINPUTWRAPPER_API HRESULT _stdcall DoDirectInput8Create(HINSTANCE a, DWORD b, REFIID c, void ** d, void * e) {
	void * ret = 0;

	HMODULE dinput8dll = NULL;	//Handle to the real dinput dll
	DInputProc func = NULL;		//Handle to the real create dinput8 function

	//char Path [MAX_PATH];
	
	//GetSystemDirectoryA (Path, MAX_PATH);
	//strcat_s (Path, 256, "\\dinput8.dll");
	wchar_t Path [MAX_PATH] = {0};
	GetDInputDllPath(Path, MAX_PATH);
	
	dinput8dll = LoadLibraryW(Path);
	func = (DInputProc) GetProcAddress(dinput8dll, "DirectInput8Create");
	if (0 == func) return E_FAIL;
	
	HRESULT hr = (func) (a, b, c, &ret, reinterpret_cast<LPUNKNOWN>(e));
	if (hr != S_OK) return hr;

	*d = CreateInputWrapper (ret);
	return S_OK;
}

