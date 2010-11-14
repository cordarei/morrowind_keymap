#include "StdAfx.h"
#include "WrapDirectInputDevice.h"


namespace {
	BYTE const ConsoleKey = 0x29;
	BYTE const MappedConsoleKey = 0xd2;//ins
	BYTE const QuoteKey = 0x28; //DIK_APOSTROPHE
	BYTE const MappedQuoteKey = 0x1b;//']' for jpn kbd
	size_t const KeyStateSize = 256;

	template <typename T>
	inline void swap(T * left, T * right) {
		T temp = *left;
		*left = *right;
		*right = temp;
	}
}


HRESULT _stdcall 
WrapDirectInputDevice::GetDeviceState(DWORD a,void* b) {
	//BYTE* b2=(BYTE*)b;
	//BYTE bytes[256];    //Create an array of 256 bytes to store the keystates
	//HRESULT hr=RealDevice->GetDeviceState(256,bytes);
	//if(hr!=DI_OK) return hr;    //Error getting device, so return
	////We only want to modify keyboard input in alternate combat mode when the player has the mouse held down
	//ZeroMemory(b,256);
	//for(int i=0;i<256;i++) {
	//	if(RemappedKeys[i]) b2[RemappedKeys[i]]=bytes[i]; else b2[i]=bytes[i];
	//}
	//return DI_OK;
	HRESULT hr=RealDevice->GetDeviceState(a, b);
	if(hr!=DI_OK) return hr;    //Error getting device, so return
	
	if (KeyStateSize == a) {
		//swap console key
		BYTE* bytes = static_cast<BYTE*>(b);
		swap(bytes + ConsoleKey, bytes + MappedConsoleKey);
		swap(bytes + QuoteKey, bytes + MappedQuoteKey);
	}
	
	return DI_OK;
}

HRESULT _stdcall 
WrapDirectInputDevice::GetDeviceData(DWORD a,DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d) {

	HRESULT hr=RealDevice->GetDeviceData(a,b,c,d);
	if( *c!=1 || b==NULL || hr!=DI_OK ) 
		return hr;

	if(b->dwOfs == ConsoleKey) {
		b->dwOfs = MappedConsoleKey;
	} else if(b->dwOfs == MappedConsoleKey) {
		b->dwOfs = ConsoleKey;
	}

	if(b->dwOfs == QuoteKey) {
		b->dwOfs = MappedQuoteKey;
	} else if(b->dwOfs == MappedQuoteKey) {
		b->dwOfs = QuoteKey;
	}

	return hr;
}