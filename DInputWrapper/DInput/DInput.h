// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された DINPUT_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// DINPUT_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
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