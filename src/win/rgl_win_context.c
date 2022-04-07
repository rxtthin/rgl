#include "win/rgl_win_context.h"
#include "rgl.h"

static LRESULT _rglWinProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

b8 
rglWinContextCreate(rglWinContext *ctx, const char *title, i32 width, i32 height) {
	RGL_ASSERT_VALID_PTR(ctx);

	ctx->hinstance = GetModuleHandle(NULL);
	STARTUPINFO si;
	GetStartupInfo(&si);

	WNDCLASSEX wc;
	wc.lpszClassName = title;
	wc.lpfnWndProc = _rglWinProcedure;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ctx->hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Failed to register window class!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	ctx->hwnd = CreateWindowA(
			wc.lpszClassName,
			title,
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			width,
			height,
			NULL,
			NULL,
			ctx->hinstance,
			NULL
	);

	ShowWindow(ctx->hwnd, si.wShowWindow);
	UpdateWindow(ctx->hwnd);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return true;
}

static LRESULT
_rglWinProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch(msg) {
		case WM_CREATE:
			break;

		case WM_CLOSE:
			DestroyWindow(_rgl_plat_ctx->hwnd);
			rglQuit();
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(_rgl_plat_ctx->hwnd, msg, wparam, lparam);
	}

	return 0;
}

void
rglWinContextDestroy(rglWinContext *ctx) {
}

f32
rglWinGetTime(void) {
}

void
rglWinStartFrame(void) {
}

void
rglWinEndFrame(void) {
}

void
rglWinSetVsync(b8 value) {
}
