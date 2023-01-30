#include "codm_entity.h"
#include "simple_logger.h"
typedef struct
{
    Uint32 entity_max;
    Entity *entity_list;
}EntityManager;

static EntityManager entity_manager = {0};

void entity_manager_close()
{
    entity_free_all();
    if (entity_manager.entity_list) free (entity_manager.entity_list);
}

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
    atexit(entity_manager_close);

}

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
    if (ent-> sprite) gf2d_sprite_free(ent->sprite);
    memset(ent, 0, sizeof(Entity));
    return;
}

void entity_draw(Entity *ent)
{
    if (!ent) return;
    if (ent->sprite)
    {
        gf2d_sprite_draw(
            ent->sprite,
            ent->position,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            (int)ent->frame);
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
    int i;
    for (i = 0; i < entity_manager.entity_max; i++)
    {
        if (!entity_manager.entity_list[i]._inuse) continue;
        entity_think(&entity_manager.entity_list[i]);
    }
    return;
}

void entity_update(Entity *ent)
{
    if(!ent) return;
    ent->frame += 0.1;
    if (ent->frame >= 16) ent->frame = 0; //Hardcoded and ugly, but cycling animation frames.
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
/*eol@eof*/