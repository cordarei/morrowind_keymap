// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ DINPUT_EXPORTS
// �V���{�����g�p���ăR���p�C������܂��B���̃V���{���́A���� DLL ���g�p����v���W�F�N�g�ł͒�`�ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// DINPUT_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef DINPUT_EXPORTS
#define DINPUT_API __declspec(dllexport)
#else
#define DINPUT_API __declspec(dllimport)
#endif

//DINPUT_API HRESULT WINAPI DirectInput8Create(
//	HINSTANCE hinst,
//    DWORD dwVersion,
//    REFIID riidltf,
//    LPVOID *ppvOut,
//    LPUNKNOWN punkOuter
//);

//DINPUT_API HRESULT _stdcall DirectInput8Create(HINSTANCE a,DWORD b,REFIID c,void** d,void* e);
extern "C" DINPUT_API HRESULT WINAPI DoDirectInput8Create(
	HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID *ppvOut,
    LPUNKNOWN punkOuter
);