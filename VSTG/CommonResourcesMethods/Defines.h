#pragma once

#define _DLL_EXPORT

#ifdef _DEBUG

#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")
#pragma comment(lib, "sfml-network-d")
#pragma comment(lib, "sfml-audio-d")

#else 

#pragma comment(lib, "sfml-system")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-graphics")
#pragma comment(lib, "sfml-network")
#pragma comment(lib, "sfml-audio")

#endif

#ifdef _DLL_EXPORT
#define __VSTG_API __declspec(dllexport)
#else
#define __VSTG_API __declspec(dllimport)
#endif
