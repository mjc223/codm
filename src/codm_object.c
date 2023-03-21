#include "codm_object.h"

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

void wall_destroy(Entity *self)
{
    entity_free(pairedObj);
    entity_free(self);
}