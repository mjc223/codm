#ifndef __CODM_PROJECTILE_H__
#define __CODM_PROJECTILE_H__

#include "gf2d_graphics.h"

#include "codm_player.h"
#include "codm_entity.h"
#include "codm_item.h"
#include "codm_hud.h"

Entity* projectile_new(Entity *parent, FacingDirection dir,
float speed, float damage, char *filename);

Entity* projectile_new_dirless(Entity *parent, float speed,
float damage, char *filename);


void projectile_think(Entity *self);

void projectile_update(Entity *self);


#endif