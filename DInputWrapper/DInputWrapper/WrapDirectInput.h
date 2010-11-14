#pragma once
#include "dinput.h"

class WrapDirectInput : public IDirectInput8A
{
public:
	WrapDirectInput(IDirectInput8A* Real) : RealInput(Real) {}

	/*** IUnknown methods ***/
    HRESULT _stdcall QueryInterface (REFIID riid, LPVOID* ppvObj) {
        return RealInput->QueryInterface(riid,ppvObj);
    }
    ULONG _stdcall AddRef(void) {
        return RealInput->AddRef();
    }
    ULONG _stdcall Release(void) {
        return RealInput->Release();
    }

	HRESULT _stdcall CreateDevice(REFGUID r,IDirectInputDevice8A** device,IUnknown* unused);

	HRESULT _stdcall EnumDevices(DWORD a,LPDIENUMDEVICESCALLBACKA b,void* c,DWORD d) {
        return RealInput->EnumDevices(a,b,c,d);
    }
    HRESULT _stdcall GetDeviceStatus(REFGUID r) {
        return RealInput->GetDeviceStatus(r);
    }
    HRESULT _stdcall RunControlPanel(HWND a,DWORD b) {
        return RealInput->RunControlPanel(a,b);
    }
    HRESULT _stdcall Initialize(HINSTANCE a,DWORD b) {
        return RealInput->Initialize(a,b);
    }
    HRESULT _stdcall FindDevice(REFGUID a,LPCSTR b,LPGUID c) {
        return RealInput->FindDevice(a,b,c);
    }
    HRESULT _stdcall EnumDevicesBySemantics(LPCSTR a,LPDIACTIONFORMATA b,LPDIENUMDEVICESBYSEMANTICSCBA c,void* d,DWORD e) {
        return RealInput->EnumDevicesBySemantics(a,b,c,d,e);
    }
    HRESULT _stdcall ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK a,LPDICONFIGUREDEVICESPARAMSA b,DWORD c,void* d) {
        return RealInput->ConfigureDevices(a,b,c,d);
    }
private:
	IDirectInput8* RealInput;
};