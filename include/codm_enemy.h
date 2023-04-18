#ifndef __CODM_ENEMY_H__
#define __CODM_ENEMY_H__

#include "gf2d_graphics.h"
#include "gf2d_font.h"
#include "gfc_vector.h"

#include "codm_entity.h"
#include "codm_hud.h"

Entity* turret_init(Vector2D vect);

void turret_think(Entity *self);

Entity* octopus_init(Vector2D vect);

void octopus_think(Entity *self);

Entity* bird_init(Vector2D vect);

void bird_think(Entity *self);

Entity* worm_init(Vector2D vect);

void worm_think(Entity *self);

#endif