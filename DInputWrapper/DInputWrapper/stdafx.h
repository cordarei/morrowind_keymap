/**
 * File: stdafx.h
 * Author: Joseph I.
 * 
 * Define standard include files.
 */

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
//Windows include files
#include <windows.h>
#include <comdef.h>


////////////////////
// useful definitions

///DirectInput version
#define DIRECTINPUT_VERSION 0x0800

/// Output debug string if in Debug mode
#ifdef RELEASE
#define DEBUGSTRING(a)
#else
#define DEBUGSTRING(a) { OutputDebugString(a); /*LOG::logline(a);*/ }
#endif

/// show error message box !!uses MessageBoxA!!
/// TODO: needs cleanup, also WHY A MACRO?!?!
#define ERRORMSG(msg)  { /*LOG::logline(msg);*/ MessageBoxA(0,msg,"MGE Error",0); /*ExitProcess(-1);*/ }