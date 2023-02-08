#ifndef __CODM_PLAYER_H__
#define __CODM_PLAYER_H__

#include "gfc_vector.h"
#include "codm_entity.h"

void player_init(Vector2D position);

void player_think(Entity *self);


#endif