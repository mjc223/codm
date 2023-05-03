#include "codm_enemy.h"
#include "codm_player.h"
#include "codm_projectile.h"

int turretCooldown = 60;
int octoTimer = 30;
int wormTimer = 180;
int birdTimer = 75;

Entity* turret_init(Vector2D vect)
{
    Entity* turret = entity_new();
    turret->id = 96;

    if(!turret) { return NULL;}

    turret->sprite = gf2d_sprite_load_all(
        "images/spin.png",
        32,
        32,
        0,
        0);

    turret->animated = 0;
    turret->frame = 0;
    turret->dir = South;
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
        projectile_new_dirless(self, 3.0, 2.0, "images/item/bolt.png");
    }
    
}

Entity* octopus_init(Vector2D vect)
{
    Entity* octo = entity_new();
    octo->id = 96;

    if(!octo) { return NULL;}

    octo->sprite = gf2d_sprite_load_all(
        "images/octo.png",
        32,
        32,
        0,
        0);

    octo->animated = 0;
    octo->frame = 0;
    vector2d_copy(octo->position, vect);
    octo->shape = gfc_shape_circle(0, 0, 10);
    octo->drawOffset = vector2d(16,16);
    octo->think = octopus_think;
    octo->currhealth = 2;
    octo->maxhealth = 2;    
    return octo;
}

void octopus_think(Entity *self)
{
    if (octoTimer == 0)
    {
        float f = gfc_random() * 10;
        octoTimer = 60;

        if (f < 2.5)
        {
            self->velocity.x = 1 * 1.5;
            self->velocity.y = 0;
        }
        else if (f < 5.0)
        {
            self->velocity.x = -1 * 1.5;
            self->velocity.y = 0;
        }
        else if (f < 7.5)
        {
            self->velocity.y = 1 * 1.5;
            self->velocity.x = 0;
            
        }
        else
        {
            self->velocity.y = -1 * 1.5;
            self->velocity.x = 0;
        }

    }
    else
    {
        octoTimer--;
    }

}

Entity* bird_init(Vector2D vect)
{
    Entity* bird = entity_new();
    bird->id = 96;

    if(!bird) { return NULL;}

    bird->sprite = gf2d_sprite_load_all(
        "images/slime.png",
        32,
        32,
        0,
        0);

    bird->animated = 0;
    bird->frame = 0;
    vector2d_copy(bird->position, vect);
    bird->shape = gfc_shape_circle(0, 0, 10);
    bird->drawOffset = vector2d(16,16);
    bird->think = octopus_think;
    bird->currhealth = 2;
    bird->maxhealth = 2;    
    return bird;
}

void bird_think(Entity *self)
{
        if (octoTimer == 0)
    {
        float f = gfc_random() * 10;
        octoTimer = 75;

        if (f < 2.5)
        {
            self->velocity.x = 1 * 2.5;
            self->velocity.y = -1 * 2.5;
        }
        else if (f < 5.0)
        {
            self->velocity.x = -1 * 2.5;
            self->velocity.y = 1 * 2.5;
        }
        else if (f < 7.5)
        {
            self->velocity.y = 1 * 2.5;
            self->velocity.x = 1 * 2.5;
        }
        else
        {
            self->velocity.y = -1 * 1.5;
            self->velocity.x = -1 * 2.5;
        }

    }
    else
    {
        octoTimer--;
    }
}

Entity* worm_init(Vector2D vect)
{
    Entity* spike = entity_new();
    spike->id = 96;

    if(!spike) { return NULL;}

    spike->sprite = gf2d_sprite_load_all(
        "images/spike.png",
        32,
        32,
        0,
        0);

    spike->animated = 0;
    spike->frame = 0;
    spike->dir = South;
    vector2d_copy(spike->position, vect);
    spike->shape = gfc_shape_circle(0, 0, 10);
    spike->drawOffset = vector2d(16,16);
    spike->think = worm_think;
    spike->currhealth = 2;
    spike->maxhealth = 2;    
    return spike;
}

void worm_think(Entity *self)
{
    if(wormTimer == 0)
    {
        Vector2D vect = self->position;
        vect.x = vect.x + gfc_random() * 100;
        vect.y = vect.y + gfc_random() * 100;

        Vector2D newVect = vector2d(vect.x, vect.y);
        vector2d_copy(self->position, newVect);

        projectile_new(self, West, 1.0, 1.0, "images/item/bolt.png");

        wormTimer = 180;
    }
    else
    {
        wormTimer--;
    }
}