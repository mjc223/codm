#include "codm_entity.h"
#include "codm_camera.h"
#include "codm_level.h"

#include "simple_logger.h"

typedef struct
{
    Uint32 entity_max;
    Entity *entity_list;
    SJson *entity_def;
}EntityManager;

/*
typedef struct
{
    Uint32 coll_max;
    Entity *coll_list;
}EntityCollisionManager;
*/

static EntityManager entity_manager = {0};
//static EntityCollisionManager coll_manager = {0};


void entity_manager_close()
{
    entity_free_all();
    if (entity_manager.entity_list) free (entity_manager.entity_list);
    slog("Entity System Closed Successfully");
}

/*
void coll_manager_close()
{
    coll_free_all();
    if(coll_manager.coll_list) free (coll_manager.coll_list);
    slog("Collision Manager Closed Successfully");
}
*/

void entity_manager_init(Uint32 max)
{
    if (max <= 0)
    {
        slog("Cannot initialize entity system: zero entities specified");
        return;
    }
    entity_manager.entity_list = gfc_allocate_array(sizeof(Entity), max);

    if(!entity_manager.entity_list)
    {
        slog("Failed to initialize entity system!");
        return;
    }
    entity_manager.entity_max = max;
    entity_manager.entity_def = sj_load("config/entities.def");
    atexit(entity_manager_close);
    slog("Entity System Initialized");

}

/*
void collision_manager_init(Uint32 max)
{
    if (max <= 0)
    {
        slog("Cannot initialize collision system: No ents specified")
        return;
    }

    coll_manager.coll_list = gfc_allocate_array(sizeof(Entity), max);

    if (!coll_manager.coll_list)
    {
        slog("Failed coll list initialization");
        return;
    }

    coll_manager.coll_max = max;
    atexit()
}
*/

void entity_free_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_max; i++)
    {
        if (!entity_manager.entity_list[i]._inuse) continue; //am I available?
        entity_free(&entity_manager.entity_list[i]);
    }
    //TODO: Ignore player freeing?

    return NULL;
}

Entity *entity_new()
{
    int i;
    for (i = 0; i < entity_manager.entity_max; i++)
    {
        if (entity_manager.entity_list[i]._inuse) continue; //am I available?
        entity_manager.entity_list[i]._inuse = 1;
        return &entity_manager.entity_list[i];
    }
    return NULL;
}

void entity_free(Entity *ent)
{
    if(!ent)
    {
        slog("No entity provided when free attempted");
        return;
    }

    if(ent->id == 1)
    {
        //save logic
        //Vector2D lastPos = ent->position;
        slog("Entity player dismissed");
    }

    if (ent-> sprite) gf2d_sprite_free(ent->sprite);
    memset(ent, 0, sizeof(Entity));
}

void entity_draw(Entity *ent)
{
    Vector2D drawPosition, camera;
    if (!ent) return;

    camera = camera_get_draw_offset();
    vector2d_add(drawPosition, ent->position, camera);

    if (ent->sprite)
    {
        gf2d_sprite_draw(
            ent->sprite,
            drawPosition,
            NULL,
            &ent->drawOffset,
            &ent->rotation,
            NULL,
            NULL,
            (Uint32)ent->frame);
    }
    return;
}

void entity_think(Entity *ent)
{
    if(!ent) return;
    if(ent->think)ent->think(ent); //has think? Call think, pass self
}

void entity_think_all()
{
    int i, j, r;
    Entity *e1, *e2;
    Shape s1, s2;
    for (i = 0; i < entity_manager.entity_max; i++)
    {
        if (!entity_manager.entity_list[i]._inuse) continue;
        

        for (j = 0; j < entity_manager.entity_max; j++)
        {
            //Shapes collide with themselves
            e1 = &entity_manager.entity_list[i];
            e2 = &entity_manager.entity_list[j];

            if (e1 == e2)
                continue;

            s1 = entity_get_shape(e1);
            s2 = entity_get_shape(e2);

            r = gfc_shape_overlap(s1, s2);
            if(r)
                slog("shape overlapping");
            if(r)
            {
                slog(e1->sprite->filepath);
                slog(e2->sprite->filepath);
            }
        }
        entity_think(&entity_manager.entity_list[i]);
    }

    return;
}

void entity_update(Entity *ent)
{
    if(!ent) return;
    
    /*
    if (ent->update)
    {if (level_shape_clip(level_get_active_level(), entity_get_shape_after_move(ent)))
        if (ent->update(ent))return;// if the update function returns 1, do not do generic update
    }
    */
   
    ent->frame += 0.1;
    if (ent->frame >= 16) ent->frame = 0; //Hardcoded and ugly, but cycling animation frames.

    if (level_shape_clip(level_get_active_level(),entity_get_shape_after_move(ent) ))
    {
        return;
    }

    vector2d_add(ent->position, ent->position, ent->velocity);
}

void entity_update_all()
{
    int i;
    for(i = 0; i < entity_manager.entity_max; i++)
    {
        if (!entity_manager.entity_list[i]._inuse) continue;
        entity_update(&entity_manager.entity_list[i]);
    }
}

void entity_draw_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_max; i++)
    {
        if (!entity_manager.entity_list[i]._inuse) continue;
        entity_draw(&entity_manager.entity_list[i]);
    }
    return;
}

SJson *entity_get_def_by_name(const char *name)
{
    if (!name) return NULL;
    return NULL;
    //what?
}

Shape entity_get_shape_after_move(Entity *ent)
{
    Shape shape = {0};
    if (!ent)return shape;
    gfc_shape_copy(&shape,ent->shape);
    gfc_shape_move(&shape,ent->position);
    gfc_shape_move(&shape,ent->velocity);
    return shape;
}

Shape entity_get_shape(Entity *ent)
{
    Shape shape = {0};
    if (!ent)return shape;
    gfc_shape_copy(&shape,ent->shape);
    gfc_shape_move(&shape,ent->position);
    return shape;
}

/*eol@eof*/