#ifndef __INTESTAZIONE_DLL
#define __INTESTAZIONE_DLL

#ifdef __BUILD_DLL__
#define XGRAPH_DLLAPI __declspec(dllexport)
#else
#define XGRAPH_DLLAPI __declspec(dllimport)
#endif

#endif