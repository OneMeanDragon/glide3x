#pragma once
#define NOMINMAX /* limits */

/*
	being as the dll has to be __stdcall you'll need the .def file
	if this was cdecl the .def file wouldent be needed, so instead
	of using the following were actually useing whats in the sdk 
	itself.
*/
#define EXTERNC extern "C"

#if defined(_WIN32)
	#define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
	#include "windows/framework.h"
#elif defined(__linux)
	#define EXPORT __attribute__((visibility("default")))
	#define IMPORT
#endif

/*
	all of the folders required for the 3dfx sdk
	are in the project propertys under vc++ 
	directorys
*/
#include <swlibs/fxmisc/3dfx.h>
#include <h5/glide3/src/glide.h>

#include <format>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

static GuTexPalette g_pal{};
