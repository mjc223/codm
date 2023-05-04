#include "simple_logger.h"
#include "codm_object.h"


int canBePushed = 1;
Entity* pairedObj;


Entity* eye_switch_init(Vector2D vect, Entity* trigger)
{
    Entity* eyeSwitch = entity_new();
    eyeSwitch->id = 80;

    pairedObj = trigger;

    if(!eyeSwitch) { return NULL;}

    eyeSwitch->sprite = gf2d_sprite_load_all(
        "images/item/crystal.png",
        32,
        32,
        0,
        0);

    eyeSwitch->animated = 0;
    eyeSwitch->frame = 0;
    vector2d_copy(eyeSwitch->position, vect);
    eyeSwitch->shape = gfc_shape_circle(0, 0, 4);
    eyeSwitch->drawOffset = vector2d(16,16);
    eyeSwitch->think = eye_think;
    eyeSwitch->type = EyeSwitch;
    eyeSwitch->currhealth = 300;
    eyeSwitch->maxhealth = 0;    
    return eyeSwitch;
}

void eye_think(Entity *self)
{
    if (!self) return;    

    if (self->currhealth < 0)
    {
        entity_free(self);
    }

    int i;
    Entity *list = get_entity_list();
    Entity *ent;

    for (i = 0; i < get_entity_max(); i++)
    {
        ent = &list[i];
        if (ent == self)
            continue;

        if(gfc_shape_overlap(entity_get_shape(self), entity_get_shape(ent)))
        {
            if(ent->type == Projectile)
            {
                wall_destroy(self);
            }
        }
    }
}

Entity* wall_trigger_init(Vector2D vect)
{
    Entity* wallTrigger = entity_new();
    wallTrigger->id = 80;

    if(!wallTrigger) { return NULL;}

    wallTrigger->sprite = gf2d_sprite_load_all(
        "images/item/chest.png",
        32,
        32,
        0,
        0);

    wallTrigger->animated = 0;
    wallTrigger->frame = 0;
    vector2d_copy(wallTrigger->position, vect);
    wallTrigger->shape = gfc_shape_circle(0, 0, 4);
    wallTrigger->drawOffset = vector2d(16,16);
    wallTrigger->currhealth = 300;
    wallTrigger->maxhealth = 0;    
    return wallTrigger;
}

Entity* trick_wall_init(Vector2D vect)
{
    Entity* trickWall = entity_new();
    trickWall->id = 80;

    if(!trickWall) { return NULL;}

    trickWall->sprite = gf2d_sprite_load_all(
        "images/trickwall.png",
        64,
        64,
        0,
        0);

    trickWall->animated = 0;
    trickWall->frame = 0;
    vector2d_copy(trickWall->position, vect);
    trickWall->shape = gfc_shape_circle(0, 0, 4);
    trickWall->drawOffset = vector2d(16,16);
    trickWall->currhealth = 300;
    trickWall->maxhealth = 0;    
    return trickWall;
}

Entity* lock_init(Vector2D vect)
{
    Entity* lock = entity_new();
    lock->id = 80;

    if(!lock) { return NULL;}

    lock->sprite = gf2d_sprite_load_all(
        "images/lock.png",
        64,
        64,
        0,
        0);

    lock->animated = 0;
    lock->frame = 0;
    lock->think = lock_unlock;
    vector2d_copy(lock->position, vect);
    lock->shape = gfc_shape_circle(0, 0, 10);
    lock->drawOffset = vector2d(16,16);
    lock->currhealth = 300;
    lock->maxhealth = 0;    
    return lock;
}

Entity* push_block_init(Vector2D vect)
{
    Entity* pushBlock = entity_new();
    pushBlock->id = 80;

    if(!pushBlock) { return NULL;}

    pushBlock->sprite = gf2d_sprite_load_all(
        "images/Brick.png",
        64,
        64,
        0,
        0);

    pushBlock->animated = 0;
    pushBlock->frame = 0;
    pushBlock->think = push_block_move;
    pushBlock->dir = East;
    vector2d_copy(pushBlock->position, vect);
    pushBlock->shape = gfc_shape_circle(0, 0, 10);
    pushBlock->drawOffset = vector2d(16,16);
    pushBlock->currhealth = 300;
    pushBlock->maxhealth = 0;
    return pushBlock;
}


void wall_destroy(Entity *self)
{
    entity_free(pairedObj);
    entity_free(self);
}

void push_block_move(Entity *self)
{
    if(canBePushed == 0)
        return;

    if(gfc_shape_overlap(entity_get_shape(self), player_get_shape() ))
    {
        Vector2D vect = self->position;
        vect.y = vect.y + 100;

        canBePushed = 0;
        vector2d_copy(self->position, vect);
    }
}

void lock_unlock(Entity *self)
{
    if(gfc_shape_overlap(entity_get_shape(self), player_get_shape() ))
    {
        entity_free(self);
    }
}