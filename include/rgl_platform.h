#ifndef __RGL_PLATFORM_H
#define __RGL_PLATFORM_H

#if defined(__linux) || defined(__linux__) || defined(linux)
	#define RGL_PLATFORM_LINUX
	#define RGL_PLATFORM_FUN(fun, ...) rglX11##fun(__VA_ARGS__)
	#define RGL_PLATFORM_CONTEXT_T  rglX11Context

	#include "x11/rgl_x11_context.h"
	#include "x11/rgl_x11_input.h"
#else
	#error RGL currently supports only linux.
#endif

#endif /* __RGL_PLATFORM_H */
