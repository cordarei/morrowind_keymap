#pragma once
#include "dinput.h"


class WrapDirectInputDevice : public IDirectInputDevice8A
{
public:
	WrapDirectInputDevice(IDirectInputDevice8* device) : RealDevice(device) {}

	/*** IUnknown methods ***/
    HRESULT _stdcall QueryInterface (REFIID riid,void** ppvObj) {
        return RealDevice->QueryInterface(riid,ppvObj);
    }
    ULONG _stdcall AddRef() {
        return RealDevice->AddRef();
    }
    ULONG _stdcall Release() {
        return RealDevice->Release();
    }


	/*** IDirectInputDevice8W methods ***/
    HRESULT _stdcall GetCapabilities(LPDIDEVCAPS a) {
        return RealDevice->GetCapabilities(a);
    }
    HRESULT _stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA a,void* b,DWORD c) {
        return RealDevice->EnumObjects(a,b,c);
    }
    HRESULT _stdcall GetProperty(REFGUID a,DIPROPHEADER* b) {
        return RealDevice->GetProperty(a,b);
    }
    HRESULT _stdcall SetProperty(REFGUID a,const DIPROPHEADER* b) {
        return RealDevice->SetProperty(a,b);
    }
    HRESULT _stdcall Acquire() {
        return RealDevice->Acquire();
    }
    HRESULT _stdcall Unacquire() {
        return RealDevice->Unacquire();
    }

	HRESULT _stdcall GetDeviceState(DWORD a,void* b);
	HRESULT _stdcall GetDeviceData(DWORD a,DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d);


	HRESULT _stdcall SetDataFormat(const DIDATAFORMAT* a) {
        return RealDevice->SetDataFormat(a);
    }
    HRESULT _stdcall SetEventNotification(HANDLE a) {
        return RealDevice->SetEventNotification(a);
    }
    HRESULT _stdcall SetCooperativeLevel(HWND a,DWORD b) {
        return RealDevice->SetCooperativeLevel(a,b);
    }
    HRESULT _stdcall GetObjectInfo(DIDEVICEOBJECTINSTANCE* a,DWORD b,DWORD c) {
        return RealDevice->GetObjectInfo(a,b,c);
    }
    HRESULT _stdcall GetDeviceInfo(DIDEVICEINSTANCE* a) {
        return RealDevice->GetDeviceInfo(a);
    }
    HRESULT _stdcall RunControlPanel(HWND a,DWORD b) {
        return RealDevice->RunControlPanel(a,b);
    }
    HRESULT _stdcall Initialize(HINSTANCE a,DWORD b,REFGUID c) {
        return RealDevice->Initialize(a,b,c);
    }
    HRESULT _stdcall CreateEffect(REFGUID a,const DIEFFECT* b,LPDIRECTINPUTEFFECT* c,IUnknown* d) {
        return RealDevice->CreateEffect(a,b,c,d);
    }
    HRESULT _stdcall EnumEffects(LPDIENUMEFFECTSCALLBACK a,void* b,DWORD c) {
        return RealDevice->EnumEffects(a,b,c);
    }
    HRESULT _stdcall GetEffectInfo(DIEFFECTINFO* a,REFGUID b) {
        return RealDevice->GetEffectInfo(a,b);
    }
    HRESULT _stdcall GetForceFeedbackState(DWORD* a) {
        return RealDevice->GetForceFeedbackState(a);
    }
    HRESULT _stdcall SendForceFeedbackCommand(DWORD a) {
        return RealDevice->SendForceFeedbackCommand(a);
    }
    HRESULT _stdcall EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK a,void* b,DWORD c) {
        return RealDevice->EnumCreatedEffectObjects(a,b,c);
    }
    HRESULT _stdcall Escape(DIEFFESCAPE* a) {
        return RealDevice->Escape(a);
    }
    HRESULT _stdcall Poll() {
        return RealDevice->Poll();
    }
    HRESULT _stdcall SendDeviceData(DWORD a,const DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d) {
        return RealDevice->SendDeviceData(a,b,c,d);
    }
    HRESULT _stdcall EnumEffectsInFile(const char* a,LPDIENUMEFFECTSINFILECALLBACK b,void* c,DWORD d) {
        return RealDevice->EnumEffectsInFile(a,b,c,d);
    }
    HRESULT _stdcall WriteEffectToFile(const char* a,DWORD b,DIFILEEFFECT* c,DWORD d) {
        return RealDevice->WriteEffectToFile(a,b,c,d);
    }
    HRESULT _stdcall BuildActionMap(DIACTIONFORMAT* a,const char* b,DWORD c) {
        return RealDevice->BuildActionMap(a,b,c);
    }
    HRESULT _stdcall SetActionMap(DIACTIONFORMAT* a,const char* b,DWORD c) {
        return RealDevice->SetActionMap(a,b,c);
    }
    HRESULT _stdcall GetImageInfo(DIDEVICEIMAGEINFOHEADER* a) {
        return RealDevice->GetImageInfo(a);
    }


private:
	LPDIRECTINPUTDEVICE8A RealDevice;
};