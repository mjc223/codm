#ifndef __CODM_ITEM_H__
#define __CODM_ITEM_H__

#include "gf2d_graphics.h"
#include "gf2d_font.h"
#include "gfc_vector.h"

#include "codm_entity.h"
#include "codm_hud.h"

Entity* bomb_pickup_init(Vector2D vect);

Entity* health_upgrade_init(Vector2D vect);

Entity* sword_upgrade_init(Vector2D vect);

void item_think(Entity *self);

Entity* sword_upgrade_init(Vector2D vect);

Entity* bow_upgrade_init(Vector2D vect);

Entity* speed_upgrade_init(Vector2D vect);

Entity* warp_init(Vector2D vect);

#endif