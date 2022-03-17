#ifndef __RGL_SPRITE_H
#define __RGL_SPRITE_H

#include "rgl_vao.h"
#include "rgl_texture.h"

typedef struct rglSprite {
	v2 position;
	v2 size;
	f32 rotation;	
	rglVao vao;
	rglTexture *texture;
} rglSprite;

b8 rglSpriteCreate(rglSprite *sprite, rglTexture *texture);
void rglSpriteDestroy(rglSprite *sprite);
void rglSpriteRender(rglSprite *sprite);

void _rglSpriteShaderCreate(void);
void _rglSpriteShaderDestroy(void);

#endif /* __RGL_SPRITE_H */
