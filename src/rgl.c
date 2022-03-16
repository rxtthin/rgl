#include "rgl.h"
#include "rgl_log.h"
#include "rgl_shader.h"

#include <sys/resource.h>
#include <sched.h>

rgl_app_data_t *g_rgl_data = 0;

static void _setup_opengl(void);
static void _start_main_loop(void);
static void _def_update(f32 dt);
static b8 _rtkit_initialize_realtime_thread();

b8 rgl_init(rgl_app_desc_t *desc) {
	RGL_ASSERT_RET_B8(desc, true);

	/* Sanity checks */
        if(desc->width <= 0)            desc->width = 960; 
        if(desc->height <= 0)           desc->height = 640;
        if(!desc->title)                desc->title = "RGL";
        if(!desc->update_f)             desc->update_f = _def_update;

	srand(time(0));

	g_rgl_data = malloc(sizeof(rgl_app_data_t));
	if(!rgl_app_data_create(g_rgl_data, desc)) {
		RGL_LOG_ERROR("Failed to create global app data");
		return false;
	}

	_setup_opengl();
	rgl_update_projection();
	rgl_shader_create_defaults();

	/* Call user-defined init func */
        if(desc->init_f) {
                desc->init_f();
        }

        _start_main_loop();

        rgl_quit();

        return true;
}

void rgl_quit(void) {
	g_rgl_data->running = false;

	/* Call user-defined quit func */
        if(g_rgl_data->desc->quit_f) {
                g_rgl_data->desc->quit_f();
        }

	rgl_shader_destroy_defaults();

	rgl_app_data_destroy(g_rgl_data);
	free(g_rgl_data);

	exit(0);
}

void rgl_set_vsync(b8 value) {
	RGL_PLATFORM_FUN(set_vsync, value);
}

void rgl_update_projection(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, g_rgl_data->width, g_rgl_data->height);
	glOrtho(0, g_rgl_data->width, g_rgl_data->height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	rgl_mat4_ortho(g_rgl_data->projection_matrix, 0, g_rgl_data->width, g_rgl_data->height, 0, -1, 1);
}

f32 rgl_get_time(void) {
	return RGL_PLATFORM_FUN(get_time);
}

void rgl_get_window_size(i32 *w, i32 *h) {
	*w = g_rgl_data->width;
	*h = g_rgl_data->height;
}

b8 rgl_app_data_create(rgl_app_data_t *data, rgl_app_desc_t *desc) {
	RGL_ASSERT_RET_B8(data, true);
	RGL_ASSERT_RET_B8(desc, true);

        data->desc = desc;
	data->width = desc->width;
	data->height = desc->width;

	data->plat_cxt = malloc(sizeof(RGL_PLATFORM_CONTEXT_T));
	if(!RGL_PLATFORM_FUN(context_initialize, data->plat_cxt, desc->title, desc->width, desc->height)) {
		RGL_LOG_ERROR("Failed to initialize platform context");
		return false;
	}

	data->audio_cxt = NULL;
	if(_rtkit_initialize_realtime_thread()) {
		data->audio_cxt = malloc(sizeof(rgl_audio_context_t));
		if(!rgl_audio_context_create(data->audio_cxt)) {
			RGL_LOG_ERROR("Failed to create audio context");
			rgl_audio_context_destroy(data->audio_cxt);
			free(data->audio_cxt);
			data->audio_cxt = NULL;
		}
	}

	return true;
}

void rgl_app_data_destroy(rgl_app_data_t *data) {
	RGL_PLATFORM_FUN(context_destroy, data->plat_cxt);
	free(data->plat_cxt);

	rgl_audio_context_destroy(data->audio_cxt);
	free(data->audio_cxt);
}

static void _setup_opengl(void) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor((f32)g_rgl_data->desc->background_color.r / 255.f, (f32)g_rgl_data->desc->background_color.g / 255.f, (f32)g_rgl_data->desc->background_color.b / 255.f, 1.f);
}

static b8 _rtkit_initialize_realtime_thread(void) {
	i32 err;
	i32 sched_policy = sched_getscheduler(0) | 0x40000000;
	struct sched_param sched_param = {0};

	struct rlimit rl;
	err = getrlimit(RLIMIT_RTTIME, &rl);

	if(err) {
		return false;
	}

	rl.rlim_max = 200000;
	rl.rlim_cur = 100000;

	err = setrlimit(RLIMIT_RTTIME, &rl);
	if(err) {
		return false;
	}

	err = sched_getparam(0, &sched_param);
	if(err) {
		return false;
	}

	err = sched_setscheduler(0, sched_policy, &sched_param);
	if(err) {
		return false;
	}

	return true;
}

static void _start_main_loop(void) {
	g_rgl_data->running = true;

        f32 dt = 0, now = RGL_PLATFORM_FUN(get_time), last = now;
        while(g_rgl_data->running) {
                /* Calculate delta time between frames */
                now = RGL_PLATFORM_FUN(get_time);
		dt = (f32)(now - last);
                last = now;

		RGL_PLATFORM_FUN(start_frame);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Call user-defined update func */
                g_rgl_data->desc->update_f(dt);

		RGL_PLATFORM_FUN(end_frame);
        }
}

static void _def_update(f32 dt) { 
        return;
}
