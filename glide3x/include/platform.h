#pragma once
#define NOMINMAX /* limits */

#define EXTERNC extern "C"

#if defined(_WIN32)
	#define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
	#include "windows/framework.h"
#elif defined(__linux)
	#define EXPORT __attribute__((visibility("default")))
	#define IMPORT
#endif

#include <swlibs/fxmisc/3dfx.h>
#include <h5/glide3/src/glide.h>

#include <format>
#include <fstream>
#include <limits>
