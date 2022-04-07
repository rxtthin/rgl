#ifndef __RGL_MATH_H
#define __RGL_MATH_H

#include "rgl_common.h"

f32 rglMathLerp_f32(f32 a, f32 b, f32 v);

f32 rglMathClamp_f32(f32 val, f32 min, f32 max);
u32 rglMathClamp_u32(u32 val, u32 min, u32 max);
i32 rglMathClamp_i32(i32 val, i32 min, i32 max);

i32 rglMathGcd_i32(i32 a, i32 b); /* Greates common divisor */

#endif /* __RGL_MATH_H */
