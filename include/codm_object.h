#ifndef __CODM_OBJECT_H__
#define __CODM_OBJECT_H__

#include "gf2d_graphics.h"

#include "codm_player.h"
#include "codm_entity.h"
#include "codm_item.h"
#include "codm_hud.h"

Entity* eye_switch_init(Vector2D vect, Entity* trigger);

Entity* wall_trigger_init(Vector2D vect);
Entity* trick_wall_init(Vector2D vect);
Entity* lock_init(Vector2D vect);
Entity* push_block_init(Vector2D vect);

void eye_think(Entity* self);
void wall_destroy();
void push_block_move(Entity *self);
void lock_unlock(Entity *self);
#endif