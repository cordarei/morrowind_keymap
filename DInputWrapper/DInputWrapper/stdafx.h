// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>
#include <comdef.h>


// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
#define DIRECTINPUT_VERSION 0x0800

#ifdef RELEASE
#define DEBUGSTRING(a)
#else
#define DEBUGSTRING(a) { OutputDebugString(a); /*LOG::logline(a);*/ }
#endif

#define ERRORMSG(msg)  { /*LOG::logline(msg);*/ MessageBoxA(0,msg,"MGE Error",0); /*ExitProcess(-1);*/ }