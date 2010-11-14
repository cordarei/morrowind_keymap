// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された DINPUTWRAPPER_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// DINPUTWRAPPER_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef DINPUTWRAPPER_EXPORTS
#define DINPUTWRAPPER_API __declspec(dllexport)
#else
#define DINPUTWRAPPER_API __declspec(dllimport)
#endif

extern "C" {
	
	//exports
	DINPUTWRAPPER_API HRESULT _stdcall DoDirectInput8Create(HINSTANCE a, DWORD b, REFIID c, void ** d, void * e);

}

