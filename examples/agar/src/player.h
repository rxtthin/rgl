#ifndef __AGAR_PLAYER_H
#define __AGAR_PLAYER_H

#include <rgl/rgl.h>

#define PLAYER_SPAWN_RADIUS 20
#define PLAYER_MOVE_SPEED 100

typedef struct player_t {
	rglV2 pos;
	rglColor color;
	f32 radius;
} player_t;

void player_spawn(player_t *player);
void player_update(player_t *player, f32 dt);
void player_draw(player_t *player);

#endif /* __AGAR_PLAYER_H */