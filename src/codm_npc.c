#include "codm_npc.h"
#include "codm_enemy.h"
#include "codm_player.h"
#include "codm_projectile.h"
#include "codm_hud.h"

#include "simple_logger.h"

Entity* npc_init(Vector2D vect, char *info)
{
    Entity* npc = entity_new();
    npc->id = 102;

    if(!npc) { return NULL;}

    npc->sprite = gf2d_sprite_load_all(
        "images/npc.png",
        16,
        16,
        0,
        0);

    npc->animated = 0;
    npc->frame = 0;
    vector2d_copy(npc->position, vect);
    npc->shape = gfc_shape_circle(0, 0, 10);
    npc->drawOffset = vector2d(16,16);
    npc->think = npc_think;
    npc->currhealth = 2;
    npc->maxhealth = 2;    
    return npc;
}

void npc_think(Entity *self)
{
    if(gfc_shape_overlap(entity_get_shape(self), player_get_shape() ))
    {    
        hud_change_message("Here's an example NPC message");
    }
}