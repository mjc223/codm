#include "simple_logger.h"
#include "simple_json.h"
#include "simple_json_types.h"
#include "simple_json_value.h"

#include "codm_input.h"
#include "codm_player.h"

static int MAXSPEED = 5;
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
    atexit(player_save());
    return;
}

void player_think(Entity *self)
{
    if (!self) return;
    UserInput moveIntent = prepare_user_input();

    if(moveIntent.Left)
        self->velocity.x = -1 * moveIntent.Left * MAXSPEED;
    else if (moveIntent.Right)
        self->velocity.x = moveIntent.Right * MAXSPEED;
    else
        self->velocity.x = 0;

    if(moveIntent.Up)
        self->velocity.y = -1 * moveIntent.Up * MAXSPEED;
    else if (moveIntent.Down)
        self->velocity.y = moveIntent.Down * MAXSPEED;
    else
        self->velocity.y = 0;
}


void player_save(const char *filename)
{
    Sjson *json, *player;

    int speed,
    meleeMult, rangedMult,
    attackSpeed, 
    currBomb, maxBomb,
    currArrow, maxArrow;

    if (!filename) return;

    json = sj_load(filename); //have a default player json
    if(!json) return;

    player = sj_object_get_value(json, "player");
    if(!player)
    {
        slog("file %s missing player object", filename);
        sj_free(json);
        return;
    }
    
    SJson spd = sj_object_get_value(player, "speed");
    speed = sj_get_integer_value(player, "speed");
    slog("The speed value is %i", speed);

    sj_object_insert(player, "speed", )
}



Vector2D player_get_position(Entity *self)
{
    return self->position;
}