#ifndef __RGL_COMMON_H
#define __RGL_COMMON_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <epoxy/gl.h>

#define RGL_PI_F 3.1415926f
#define RGL_PI_2F 2.0f*RGL_PI_F

#define RGL_RAND_F32 ((f32)rand() / (f32)RAND_MAX)
#define RGL_RAND_U8 (u8)(rand() % 256) 
#define RGL_RAND_RANGE_F32(min, max) (RGL_RAND_F32 * (max-min) + min)
#define RGL_RAND_RANGE_I32(min, max) (rand() % (max-min) + min)

typedef int8_t          i8;
typedef int16_t         i16;
typedef int32_t         i32;
typedef int64_t         i64;
typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;
typedef float           f32;
typedef double          f64;
typedef bool            b8;

#include "rgl_math.h"
#include "rgl_v2.h"
#include "rgl_mat4.h"
#include "rgl_color.h"
#include "rgl_log.h"

#ifdef RGL_BUILD
	#include "rgl_assert.h"
#endif

typedef void (*rglAppUpdateFunc)(f32 dt);
typedef void (*rglAppQuitFunc)(void);
typedef void (*rglAppInitFunc)(void);
typedef void (*rglAppDrawFunc)(void);

#define rglSwap(a, b) _rglSwap(a, b, sizeof(a))
void _rglSwap(void *a, void *b, size_t size);

#endif /* __RGL_COMMON_H */
