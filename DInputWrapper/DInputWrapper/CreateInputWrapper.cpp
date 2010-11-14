#include "stdafx.h"
#include <dinput.h>
#include "WrapDirectInput.h"

///////// Implementation
//typedef HRESULT (_stdcall *DInputProc)(HINSTANCE,DWORD,REFIID,LPVOID,LPUNKNOWN);

void* CreateInputWrapper(void* real) {
	IDirectInput8A* Real=(IDirectInput8A*)real;
	return new WrapDirectInput(Real);
}