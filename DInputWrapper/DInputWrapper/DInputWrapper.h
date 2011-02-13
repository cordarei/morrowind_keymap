/**
 * File: DInputWrapper.h
 * Author: Joseph I.
 *
 * Main header file. Declares the function to get our
 * DInput device wrapper.
 *
 * Note: for some reason dllexport was not working, so this function
 *	     is actually exported using `exports.def`. This is not ideal,
 *	     but for now we do it this way.
 */

///Export/Import symbols
#ifdef DINPUTWRAPPER_EXPORTS
#define DINPUTWRAPPER_API __declspec(dllexport)
#else
#define DINPUTWRAPPER_API __declspec(dllimport)
#endif


/**
 * \function DoDirectInput8Create
 * \brief Wraps a normal DInput device with our wrapper class.
 *
 * Loads "dinput8.dll" from the system directory and creates the requested device,
 * then creates a wrapper device around it and returns the wrapper.
 */
extern "C" DINPUTWRAPPER_API HRESULT _stdcall DoDirectInput8Create(HINSTANCE a, DWORD b, REFIID c, void ** d, void * e);