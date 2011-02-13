/**
 * File: DInput.h
 * Author: Joseph I.
 *
 * Main header file. Declares the hook function to get our
 * DInput device wrapper.
 *
 * Note: for some reason dllexport was not working, so this function
 *	     is actually exported using `exports.def`. This is not ideal,
 *	     but for now we do it this way.
 */

///Export/Import symbols
#ifdef DINPUT_EXPORTS
#define DINPUT_API __declspec(dllexport)
#else
#define DINPUT_API __declspec(dllimport)
#endif


///wrapper DLL filename
#define WRAPPER_DLL_PATH L"DInputWrapper.dll"


//windows API
//DINPUT_API HRESULT WINAPI DirectInput8Create(
//	HINSTANCE hinst,
//    DWORD dwVersion,
//    REFIID riidltf,
//    LPVOID *ppvOut,
//    LPUNKNOWN punkOuter
//);

/**
 * \function DoDirectInput8Create
 * \brief Wraps a normal DInput device with our wrapper class.
 *
 * Loads "DInputWrapper.dll" and calls its version of \code DirectInput8Create ,
 * which creates our wrapper device and returns it.
 */
extern "C" DINPUT_API HRESULT WINAPI DoDirectInput8Create(
	HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID *ppvOut,
    LPUNKNOWN punkOuter
);
//DINPUT_API HRESULT _stdcall DirectInput8Create(HINSTANCE a,DWORD b,REFIID c,void** d,void* e);