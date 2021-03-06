#ifndef __RGL_COLOR_H
#define __RGL_COLOR_H

#include "rgl_common.h"

typedef struct rglColor {
        union {
                u8 rgb[3]; 
                struct {
                        u8 r, g, b;
                };
        };
} rglColor;

#define RGL_RGB(r, g, b) (rglColor) { .rgb = {r, g, b}  }
#define RGL_COLOR_RAND ((rglColor){.rgb = {RGL_RAND_U8,RGL_RAND_U8,RGL_RAND_U8}})

#define RGL_BLACK         RGL_RGB(0, 0, 0)
#define RGL_WHITE         RGL_RGB(255, 255, 255)
#define RGL_RED           RGL_RGB(255, 0, 0)
#define RGL_GREEN         RGL_RGB(0, 255, 0)
#define RGL_BLUE          RGL_RGB(0, 0, 255)

#endif /* __RGL_COLOR_H */
