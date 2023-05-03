#ifndef __CODM_NPC_H__
#define __CODM_NPC_H__

#include "gf2d_graphics.h"
#include "gf2d_font.h"
#include "gfc_vector.h"

#include "codm_entity.h"
#include "codm_hud.h"

Entity* npc_init(Vector2D vect, char *info);

void npc_think(Entity *self);

#endif