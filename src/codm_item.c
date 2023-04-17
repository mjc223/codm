#include "codm_item.h"
#include "codm_player.h"
#include "simple_logger.h"
#include "codm_level.h"

Entity* health_upgrade_init(Vector2D vect)
{
    Entity* healthUp = entity_new();
    healthUp->id = 255;

    if(!healthUp) { return NULL;}

    healthUp->sprite = gf2d_sprite_load_all(
        "images/item/heart.png",
        32,
        32,
        0,
        0);

    healthUp->animated = 0;
    healthUp->frame = 0;
    vector2d_copy(healthUp->position, vect);
    healthUp->shape = gfc_shape_circle(0, 0, 10);
    healthUp->drawOffset = vector2d(16,16);
    healthUp->think = item_think;
    healthUp->type = HealthUp;
    healthUp->currhealth = 300;
    healthUp->maxhealth = 0;    
    return healthUp;
}

Entity* sword_upgrade_init(Vector2D vect)
{
    Entity* swordUp = entity_new();
    swordUp->id = 255;

    if(!swordUp) { return NULL;}

    swordUp->sprite = gf2d_sprite_load_all(
        "images/item/glove.png",
        32,
        32,
        0,
        0);

    swordUp->animated = 0;
    swordUp->frame = 0;
    vector2d_copy(swordUp->position, vect);
    swordUp->shape = gfc_shape_circle(0, 0, 10);
    swordUp->drawOffset = vector2d(16,16);
    swordUp->think = item_think;
    swordUp->type = SwordUp;
    swordUp->currhealth = 300;
    swordUp->maxhealth = 0;    
    return swordUp;
}

Entity* bow_upgrade_init(Vector2D vect)
{
    Entity* arrowUp = entity_new();
    arrowUp->id = 255;

    if(!arrowUp) { return NULL;}

    arrowUp->sprite = gf2d_sprite_load_all(
        "images/item/range.png",
        32,
        32,
        0,
        0);

    arrowUp->animated = 0;
    arrowUp->frame = 0;
    vector2d_copy(arrowUp->position, vect);
    arrowUp->shape = gfc_shape_circle(0, 0, 10);
    arrowUp->drawOffset = vector2d(16,16);
    arrowUp->think = item_think;
    arrowUp->type = BowUp;
    arrowUp->currhealth = 300;
    arrowUp->maxhealth = 0;   
    return arrowUp; 
}

Entity* speed_upgrade_init(Vector2D vect)
{
    Entity* speedUp = entity_new();
    speedUp->id = 255;

    if(!speedUp) { return NULL;}

    speedUp->sprite = gf2d_sprite_load_all(
        "images/item/boot.png",
        32,
        32,
        0,
        0);

    speedUp->animated = 0;
    speedUp->frame = 0;
    vector2d_copy(speedUp->position, vect);
    speedUp->shape = gfc_shape_circle(0, 0, 10);
    speedUp->drawOffset = vector2d(16,16);
    speedUp->think = item_think;
    speedUp->type = SpeedUp;
    speedUp->currhealth = 300;
    speedUp->maxhealth = 0;   
    return speedUp;
}

Entity* warp_init(Vector2D vect)
{
    Entity* warp = entity_new();
    warp->id = 512;

    if(!warp) { return NULL;}

    warp->sprite = gf2d_sprite_load_all(
        "images/item/chest.png",
        32,
        32,
        0,
        0);

    warp->animated = 0;
    warp->frame = 0;
    vector2d_copy(warp->position, vect);
    warp->shape = gfc_shape_circle(0, 0, 10);
    warp->drawOffset = vector2d(16,16);
    warp->think = item_think;
    warp->type = Warp;
    warp->currhealth = 300;
    warp->maxhealth = 0;   

    warp->info = "config/test2.level";
    return warp;
}


void item_think(Entity *self)
{
    if (!self) return;    

    if (self->currhealth < 0)
    {
        entity_free(self);
    }

    if(gfc_shape_overlap(entity_get_shape(self), player_get_shape() ))
    {   
        if(self->type == HealthUp)
        {
            player_set_max_health(1);
            hud_change_message("Health up by 1");
        }
        else if (self->type == SwordUp)
        {
            player_upgrade_sword_damage(1);
            hud_change_message("Sword damage up by 1");
        }
        else if (self->type == BowUp)
        {
            player_upgrade_bow_damage(1);
            hud_change_message("Bow damage up by 1");
        }
        else if (self->type == SpeedUp)
        {
            player_upgrade_speed(1);
            hud_change_message("Speed increased by 1");
        }
        else if (self->type == Warp)
        {
            Level *level;
            level = level_load(self->info);
            level_set_active_level(level);
            hud_change_message("Player is warping");
        }

        entity_free(self);
    }
}