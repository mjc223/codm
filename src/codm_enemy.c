#include "codm_enemy.h"
#include "codm_player.h"
#include "codm_projectile.h"

int turretCooldown = 60;

Entity* turret_init(Vector2D vect)
{
    Entity* turret = entity_new();
    turret->id = 96;

    if(!turret) { return NULL;}

    turret->sprite = gf2d_sprite_load_all(
        "images/item/glove.png",
        64,
        64,
        0,
        0);

    turret->animated = 0;
    turret->frame = 0;
    vector2d_copy(turret->position, vect);
    turret->shape = gfc_shape_circle(0, 0, 10);
    turret->drawOffset = vector2d(16,16);
    turret->think = turret_think;
    turret->currhealth = 2;
    turret->maxhealth = 2;    
    return turret;
}

void turret_think(Entity *self)
{
    turretCooldown -= 1;
    if(turretCooldown <= 0) 
    {
        turretCooldown = 60;
        projectile_new(self, South, 3.0, 2.0, "images/item/bolt.png");
    }
}

Entity* octopus_init(Vector2D vect)
{

}

void octopus_think(Entity *self)
{

}

Entity* bird_init(Vector2D vect)
{

}

void bird_think(Entity *self)
{

}

Entity* worm_init(Vector2D vect)
{

}

void worm_think(Entity *self)
{
    
}