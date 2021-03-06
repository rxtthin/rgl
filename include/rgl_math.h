#ifndef __RGL_MATH_H
#define __RGL_MATH_H

#include "rgl_common.h"

#define rglMathLerp(a, b, v) ((a * (1.0f - v)) + (b * v))

#define rglMathClamp(v, min, max) \
	if(v < min) v = min; \
	else if(v > max) v = max;

i32 rglMathGcd_i32(i32 a, i32 b); /* Greates common divisor */

#endif /* __RGL_MATH_H */
