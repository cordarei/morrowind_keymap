/**
 * File: CreateInputWrapper.h
 * Author: Joseph I.
 *
 * Defines the function to wrap a DInput device.
 * Separated from DInputWrapper.cpp to separate
 * Windows API use from our functions and DInput.
 */

#include "stdafx.h"
#include <dinput.h>
#include "WrapDirectInput.h"

///////// Implementation
//typedef HRESULT (_stdcall *DInputProc)(HINSTANCE,DWORD,REFIID,LPVOID,LPUNKNOWN);

/**
 * \function CreateInputWrapper
 * \brief Wraps given DInput device with a wrapper device
 *
 * Should probably do something about using void pointers.
 * Also: exception safety with `new`?
 *
 * \param real the real DInput device from dinput8.dll
 * \return the wrapper device
 */
void* CreateInputWrapper(void* real) {
	IDirectInput8A* Real=(IDirectInput8A*)real;
	return new WrapDirectInput(Real);
}