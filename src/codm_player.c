#include "simple_logger.h"
#include "codm_input.h"
#include "codm_player.h"

static int SPEED = 3;
static Entity *plr = {0};

void player_think(Entity *self);

void player_init(Vector2D pos)
{
    plr = entity_new();
    plr->id = 1;
    slog("player entity created");
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
    UserInput moveIntent = prepare_user_input();

    if(moveIntent.Left)
        self->velocity.x = -1 * moveIntent.Left * SPEED;
    else if (moveIntent.Right)
        self->velocity.x = moveIntent.Right * SPEED;
    else
        self->velocity.x = 0;

    if(moveIntent.Up)
        self->velocity.y = -1 * moveIntent.Up * SPEED;
    else if (moveIntent.Down)
        self->velocity.y = moveIntent.Down * SPEED;
    else
        self->velocity.y = 0;    
}

Vector2D player_get_position(Entity *self)
{
    return self->position;
}