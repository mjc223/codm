#ifndef __CODM_OBJECT_H__
#define __CODM_OBJECT_H__

#include "gf2d_graphics.h"

#include "codm_player.h"
#include "codm_entity.h"
#include "codm_item.h"
#include "codm_hud.h"

Entity* eye_switch_init(Vector2D vect, Entity* trigger);

Entity* wall_trigger_init(Vector2D vect);

void eye_think(Entity* self);

void wall_destroy();

#endif