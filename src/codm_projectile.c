#include "codm_projectile.h"
#include "codm_entity.h"
#include "simple_logger.h"
int playerOwned = 0;

Entity* myParent;

Entity* projectile_new(Entity *parent, FacingDirection dir, float speed, float damage, char *filename)
{
    Entity* proj;
    proj = entity_new();
    
    if (!proj) return NULL;


    proj->sprite = gf2d_sprite_load_all(
        filename,
        32,
        32,
        0,
        0);
    proj->drawOffset = vector2d(16,16);
    vector2d_copy(proj->position, parent->position);

    proj->think = projectile_think;
    proj->update = projectile_update;
    proj->shape = gfc_shape_circle(0, 0, 3);
    if(parent->id = 1)
        playerOwned = 1;
    proj->dir = parent->dir;

    proj->maxhealth = 500;
    proj->currhealth = 500;
    
    proj->speed = speed;
    proj->damage = damage;
    proj->type = Projectile;
    
    myParent = parent;
}

void projectile_think(Entity* self)
{
    self->currhealth -= 1;
    if(self->currhealth <= 0)
        entity_free(self);
}

void projectile_update(Entity *self)
{
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
            if(ent->type == Living)
            {
                ent->currhealth -= self->damage;
                entity_free(self);
            }
        }
    }
    
    /*
    if(self->id = 57)
    {
        Vector2D *vect;
        vector2d_move_towards(vect, self->position, player_get_position(), 10);
        self->velocity.x = vect->x;
        self->velocity.y = vect->y;
    }
    */
    
    switch (self->dir)
    {
    case North:
        self->velocity.y = -1 * self->speed;
        break;
    
    case South:
        self->velocity.y = +1 * self->speed;
        break;

    case West:
        self->velocity.x = -1 * self->speed;
        break;

    case East:
        self->velocity.x = +1 * self->speed;
        break;

    default:
        break;
    }
}  


Entity* projectile_new_dirless(Entity *parent, float speed, float damage, char *filename)
{
    Entity* proj;
    proj = entity_new();
    
    if (!proj) return NULL;


    proj->sprite = gf2d_sprite_load_all(
        filename,
        32,
        32,
        0,
        0);
    proj->drawOffset = vector2d(16,16);
    vector2d_copy(proj->position, parent->position);

    proj->think = projectile_think;
    proj->update = projectile_update;
    proj->shape = gfc_shape_circle(0, 0, 3);
    if(parent->id = 1)
        playerOwned = 1;


    proj->maxhealth = 500;
    proj->currhealth = 500;
    

    proj->id = 57;

    proj->speed = speed;
    proj->damage = damage;
    proj->type = Projectile;
    
    myParent = parent;
    
}