// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>
#include <comdef.h>


// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#define DIRECTINPUT_VERSION 0x0800

#ifdef RELEASE
#define DEBUGSTRING(a)
#else
#define DEBUGSTRING(a) { OutputDebugString(a); /*LOG::logline(a);*/ }
#endif

#define ERRORMSG(msg)  { /*LOG::logline(msg);*/ MessageBoxA(0,msg,"MGE Error",0); /*ExitProcess(-1);*/ }