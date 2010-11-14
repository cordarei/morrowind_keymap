#include "StdAfx.h"
#include "WrapDirectInput.h"
#include "WrapDirectInputDevice.h"

HRESULT _stdcall
	WrapDirectInput::CreateDevice(REFGUID r,IDirectInputDevice8A** device,IUnknown* unused)
{
	if(r!=GUID_SysKeyboard) {
		return RealInput->CreateDevice(r,device,unused);
	} else {
		IDirectInputDevice8A* RealDevice;

		HRESULT hr=RealInput->CreateDevice(r,&RealDevice,unused);
		if(hr!=DI_OK) return hr;

		*device=new WrapDirectInputDevice(RealDevice);

		return DI_OK;
	}
}