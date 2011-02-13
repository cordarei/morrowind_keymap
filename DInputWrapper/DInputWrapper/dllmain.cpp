/**
 * File: dllmain.cpp
 * Author: Joseph I.
 *
 * Entry point when the DLL is loaded.
 * There is nothing to do here for now.
 *
 * TODO: add config file loading here? Check for
 *		 problems with DLL dependency loading sequence.
 */

#include "stdafx.h"

/**
 * \function DllMain
 * \brief Entry point when DLL is loaded
 */
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

