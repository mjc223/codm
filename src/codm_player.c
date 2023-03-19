#include "simple_logger.h"
#include "simple_json.h"

#include "codm_input.h"
#include "codm_player.h"

static Entity *plr = {0};
static char* filename = "config/player.def";
static char* invfilename = "config/playerinv.def";

SJson *jsonPlayer, *jsonPlayerInv;


void player_init(Vector2D pos)
{
    PlayerData *data;
    PlayerInv *inv;
    plr = entity_new();
    plr->id = 1;
    slog("player entity created");
    if(!plr) return;

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
    player_load(data);

    inv = gfc_allocate_array(sizeof(PlayerInv), 1);
    player_inv_load(inv);

    data->inv = inv;
    plr->data = data;
    

    vector2d_copy(plr->position, vector2d(data->xPos, data->yPos));
    atexit(player_save);
    return;
}

void player_load(PlayerData *data)
{
    SJson *playerObj;

    if (!filename) return;

    jsonPlayer = sj_load(filename); //have a default player json
    if(!jsonPlayer) return;

    playerObj = sj_object_get_value(jsonPlayer, "player");
    if(!playerObj)
    {
        slog("file %s missing player object", filename);
        sj_free(jsonPlayer);
        return;
    }

    sj_object_get_value_as_float(playerObj, "xPos", &data->xPos);
    sj_object_get_value_as_float(playerObj, "yPos", &data->yPos);

    sj_object_get_value_as_int(playerObj, "speed", &data->speed);

    sj_object_get_value_as_int(playerObj, "meleeMult", &data->meleeMult);
    sj_object_get_value_as_int(playerObj, "arrowMult", &data->arrowMult);

    sj_object_get_value_as_int(playerObj, "attackSpeed", &data->attackSpeed);

    sj_object_get_value_as_int(playerObj, "currBomb", &data->currBomb);
    sj_object_get_value_as_int(playerObj, "maxBomb", &data->maxBomb);

    sj_object_get_value_as_int(playerObj, "currArrow", &data->currArrow);
    sj_object_get_value_as_int(playerObj, "maxArrow", &data->maxArrow);
}

void player_inv_load(PlayerInv *inv)
{
    SJson *playerInvObj;

    if (!invfilename) return;

    jsonPlayerInv = sj_load(invfilename); //have a default player json
    if(!jsonPlayerInv) return;

    playerInvObj = sj_object_get_value(jsonPlayerInv, "player");
    if(!playerInvObj)
    {
        slog("file %s missing player object", invfilename);
        sj_free(jsonPlayerInv);
        return;
    }

    sj_object_get_value_as_int(playerInvObj, "hasBomb", &inv->hasBomb);
    sj_object_get_value_as_int(playerInvObj, "hasBow", &inv->hasBow);
    sj_object_get_value_as_int(playerInvObj, "hasCandle", &inv->hasCandle);
}

void player_save()
{
    SJson *jsonCopy, *playerNew;

    if (!filename) return;

    if(!jsonPlayer) return;

    jsonCopy = sj_copy(jsonPlayer);

    
    playerNew = player_save_writer();

    sj_object_delete_key(jsonCopy, "player");

    sj_object_insert(jsonCopy, "player", playerNew);

    sj_save(jsonCopy, "config/player.def");

}

SJson* player_save_writer()
{
    SJson *newXPos, *newYPos, *newSpeed, *newMeleeMult, *newArrowMult,
    *newAttackSpeed, *newCurrBomb, *newMaxBomb, *newCurrArrow, *newMaxArrow;

    SJson *newPlayer;
    newPlayer = sj_object_new();

    PlayerData *pd = plr->data;
    
    pd->xPos = plr->position.x;
    pd->yPos = plr->position.y;

    newXPos = sj_new_float(pd->xPos);
    newYPos = sj_new_float(pd->yPos);

    newSpeed = sj_new_int(pd->speed);

    newMeleeMult = sj_new_int(pd->meleeMult);
    newArrowMult = sj_new_int(pd->arrowMult);
    newAttackSpeed = sj_new_int(pd->attackSpeed);

    newCurrBomb = sj_new_int(pd->currBomb);
    newMaxBomb = sj_new_int(pd->maxBomb);

    newCurrArrow = sj_new_int(pd->currArrow);
    newMaxArrow = sj_new_int(pd->maxArrow);

    sj_object_insert(newPlayer, "xPos", newXPos);
    sj_object_insert(newPlayer, "yPos", newYPos);
    sj_object_insert(newPlayer, "speed", newSpeed);
    sj_object_insert(newPlayer, "meleeMult", newMeleeMult);
    sj_object_insert(newPlayer, "arrowMult", newArrowMult);
    sj_object_insert(newPlayer, "attackSpeed", newAttackSpeed);
    sj_object_insert(newPlayer, "currBomb", newCurrBomb);
    sj_object_insert(newPlayer, "maxBomb", newMaxBomb);
    sj_object_insert(newPlayer, "currArrow", newCurrArrow);
    sj_object_insert(newPlayer, "maxArrow", newMaxArrow);


    return newPlayer;
}

void player_think(Entity *self)
{
    if (!self) return;
    UserInput moveIntent = prepare_user_input();
    PlayerData *pd = plr->data;

    pd->xPos = self->position.x;
    pd->yPos = self->position.y;
    
    if(moveIntent.Left)
        self->velocity.x = -1 * moveIntent.Left * pd->speed;
    else if (moveIntent.Right)
        self->velocity.x = moveIntent.Right * pd->speed;
    else
        self->velocity.x = 0;

    if(moveIntent.Up)
        self->velocity.y = -1 * moveIntent.Up * pd->speed;
    else if (moveIntent.Down)
        self->velocity.y = moveIntent.Down * pd->speed;
    else
        self->velocity.y = 0;
}


Vector2D player_get_position(Entity *self)
{
    return self->position;
}

PlayerData* player_get_pd()
{
    return plr->data;
}

int player_get_curr_health()
{
    return plr->currhealth;
}