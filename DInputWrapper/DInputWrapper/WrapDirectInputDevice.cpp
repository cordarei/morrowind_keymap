/**
 * File: WrapDirectInput.h
 * Author: Joseph I.
 *
 * WrapDirectInputDevice class implementation.
 *
 * Note: use ANSI version (~A) of all DX classes
 * TODO: document parameters (what are a,b,c,d??)
 */
#include "StdAfx.h"
#include "WrapDirectInputDevice.h"


namespace {
	/// Default console key for Morrowind ('~' on US keyboard)
	BYTE const ConsoleKey = 0x29;
	/// Mapped console key (Insert)
	BYTE const MappedConsoleKey = 0xd2;//ins
	/// Default quote key for Morrowind, for typing single and double quotes ('\'' on US keyboard)
	BYTE const QuoteKey = 0x28; //DIK_APOSTROPHE
	/// Mapped quote key (']' on JIS keyboard)
	BYTE const MappedQuoteKey = 0x1b;//']' for jpn kbd
	/// Keyboard state size (256 scan codes)
	size_t const KeyStateSize = 256;

	/**
	 * \function swap
	 * \brief swap two pointers
	 *
	 * \templateparam T type pointed to
	 */
	template <typename T>
	inline void swap(T * left, T * right) {
		T temp = *left;
		*left = *right;
		*right = temp;
	}
}


/**
 * \method WrapDirectInputDevice::GetDeviceState
 * \brief gets the (re-mapped) keyboard key state
 *
 * Right now just swaps BYTES pointed to. Eventually there will
 * probably be a configuration file and this will get more
 * sophisticated.
 */
HRESULT _stdcall 
WrapDirectInputDevice::GetDeviceState(DWORD a,void* b) {
	HRESULT hr=RealDevice->GetDeviceState(a, b);
	if(hr!=DI_OK) return hr;    //Error getting device state, so return
	
	if (KeyStateSize == a) {
		//swap console key
		BYTE* bytes = static_cast<BYTE*>(b);
		swap(bytes + ConsoleKey, bytes + MappedConsoleKey);
		swap(bytes + QuoteKey, bytes + MappedQuoteKey);
	}
	
	return DI_OK;
}

/**
 * \method WrapDirectInputDevice::GetDeviceState
 * \brief gets the (re-mapped) key state of a specific key
 *
 * Right now just switches offsets. Eventually there will
 * probably be a configuration file and this will get more
 * sophisticated.
 */
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