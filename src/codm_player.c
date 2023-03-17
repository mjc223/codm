#include "simple_logger.h"
#include "simple_json.h"

#include "codm_input.h"
#include "codm_player.h"

static int MAXSPEED = 3;
static Entity *plr = {0};
static char* filename = "config/player.def";
SJson *playerSaveCopy;
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


void player_save()
{
    slog("reached trigger");
    SJson *json, *player, *psl;
    SJson *kil;

    SJString *s;
    char *str;

    char *name;
    int speed,
    meleeMult, rangeMult,
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
    name = sj_object_get_value_as_string(player, "name");  
    speed = SDL_atoi(sj_object_get_value_as_string(player, "speed"));

    meleeMult = SDL_atoi(sj_object_get_value_as_string(player, "meleeMult"));

    playerSaveCopy = sj_copy(json);

    psl = sj_object_get_value(playerSaveCopy, "player");

    sj_object_delete_key(psl, "speed");

    SJson *newSpeed;
    newSpeed = sj_new_int(5);
    
    sj_object_insert(psl, "speed", newSpeed);

    sj_save(psl, "config/player2.def");

    //slog(s->text);
    //sj_string_set()
    //meleeMult = SDL_atoi(kil->v);
    //rangedMult = SDL_atoi(sj_object_get_value_as_string(player, "rangedMult"));

    //attackSpeed = SDL_atoi(sj_object_get_value_as_string(player, "attackSpeed"));
    
  //  currBomb = SDL_atoi(sj_object_get_value_as_string(player, "currBomb"));
    //maxBomb = SDL_atoi(sj_object_get_value_as_string(player, "maxBomb"));

    //currArrow = SDL_atoi(sj_object_get_value_as_string(player, "currArrow"));
    //maxArrow = SDL_atoi(sj_object_get_value_as_string(player, "maxArrow"));
    
    //slog("The value is %s %i ");
}



Vector2D player_get_position(Entity *self)
{
    return self->position;
}