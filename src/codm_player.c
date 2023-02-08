#include "simple_logger.h"
#include "codm_input.h"
#include "codm_player.h"

static int SPEED = 3;
static Entity *plr = {0};

void player_think(Entity *self);

void player_init(Vector2D pos)
{
    plr = entity_new();
    if(!plr) return NULL;
    plr->sprite = gf2d_sprite_load_all(
        "images/pointer.png",
        128,
        128,
        16,
        0);
    plr->think = player_think;
    vector2d_copy(plr->position, pos);

    return;
}

void player_think(Entity *self)
{
    if (!self) return;
    Vector2D moveIntent = prepare_user_input();
    self->velocity.x = moveIntent.x * SPEED;
    self->velocity.y = moveIntent.y * SPEED;
}