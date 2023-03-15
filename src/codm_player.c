#include "simple_logger.h"
#include "simple_json.h"

#include "codm_input.h"
#include "codm_player.h"

static int SPEED = 3;
static Entity *plr = {0};

typedef struct
{
    int meleeMult;
    int rangeMult;
    int attackSpeed;

    int currBomb;
    int maxBomb;

    int currArrow;
    int maxArrow;
}PlayerData;

void player_init(Vector2D pos)
{
    PlayerData *data;
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
    
    plr->shape = gfc_shape_circle(0,0,10);
    plr->drawOffset = vector2d(16,16);
    plr->think = player_think;
    plr->currhealth = 6;
    plr->maxhealth = 6;

    data = gfc_allocate_array(sizeof(PlayerData), 1);        
    if (data)
    {
        data->meleeMult = 1;
        data->rangeMult = 1;
        
        data->currBomb = 0;
        data->maxBomb = 0;

        data->currArrow = 0;
        data->maxArrow = 10;
        plr->data = data;
    }


    vector2d_copy(plr->position, pos);
    atexit(player_save);
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


void player_save()
{
    
}



Vector2D player_get_position(Entity *self)
{
    return self->position;
}