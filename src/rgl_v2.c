#include "rgl_v2.h"
#include <math.h>

/* TODO: Should I assert the parameters in these functions? */

void rgl_v2_cpy(v2 *v, v2 *dest) {
	dest->x = v->x;
	dest->y = v->y;
}

void rgl_v2_setf(v2 *v, f32 f) {
	v->x = f;
	v->y = f;
}

void rgl_v2_zero(v2 *v) {
	v->x = 0;
	v->y = 0;
}

void rgl_v2_add(v2 *a, v2 *b, v2 *dest) {
	dest->x = a->x + b->x;
	dest->y = a->y + b->y;
}

void rgl_v2_addf(v2 *v, f32 f, v2 *dest) {
	dest->x = v->x + f;
	dest->y = v->y + f;
}

void rgl_v2_sub(v2 *a, v2 *b, v2 *dest) {
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;
}

void rgl_v2_subf(v2 *v, f32 f, v2 *dest) {
	dest->x = v->x - f;
	dest->y = v->y - f;
}

void rgl_v2_mul(v2 *a, v2 *b, v2 *dest) {
	dest->x = a->x * b->x;
	dest->y = a->y * b->y;
}

void rgl_v2_mulf(v2 *v, f32 f, v2 *dest) {
	dest->x = v->x * f;
	dest->y = v->y * f;
}

void rgl_v2_div(v2 *a, v2 *b, v2 *dest) {
	if(b->x != 0) dest->x = a->x / b->x;
	if(b->y != 0) dest->y = a->y / b->y;
}

void rgl_v2_divf(v2 *v, f32 f, v2 *dest) {
	if(v != 0) {
		dest->x = v->x / f;
		dest->y = v->y / f;
	}
}

void rgl_v2_normalize(v2 *v, v2 *dest) {
	f32 len = rgl_v2_len(v);

	if(len != 0) {
		dest->x /= len;
		dest->y /= len;
	}
}

f32 rgl_v2_len(v2 *a) {
	return sqrtf(a->x*a->x + a->y*a->y);
}

void rgl_v2_print(v2 *a, b8 newline) {
	printf("[%f, %f]", a->x, a->y);

	if(newline) {
		printf("\n");
	}
}
