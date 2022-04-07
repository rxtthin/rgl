#ifndef __RGL_WIN_CONTEXT_H
#define __RGL_WIN_CONTEXT_H

#include "../rgl_common.h"

#define WIN32_LEAN_AND_MEAN
#include <epoxy/gl.h>
#include <epoxy/wgl.h>

typedef struct rglWinContext {
	HINSTANCE hinstance;
	HWND hwnd;
} rglWinContext;

b8 rglWinContextCreate(rglWinContext *ctx, const char *title, i32 width, i32 height);
void rglWinContextDestroy(rglWinContext *ctx);

f32 rglWinGetTime(void);
void rglWinStartFrame(void);
void rglWinEndFrame(void);
void rglWinSetVsync(b8 value);

#endif /* __RGL_WIN_CONTEXT_H */
