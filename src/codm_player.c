#include "simple_logger.h"
#include "simple_json.h"

#include "codm_input.h"
#include "codm_player.h"
#include "codm_projectile.h"
#include "gfc_audio.h"

static Entity *plr = {0};
static char* filename = "config/player.def";
static char* invfilename = "config/playerinv.def";

SJson *jsonPlayer, *jsonPlayerInv;

enum InventoryOrder {ItemEmpty, ItemBomb, ItemBow, ItemCandle}; 
int InventorySize = ItemCandle - ItemEmpty;

int swapCooldown = 0;
int attack2Cooldown = 0;

Sound* bowSound;

void player_init(Vector2D pos)
{
    PlayerData *data;
    PlayerInv *inv;
    plr = entity_new();
    plr->id = 1;
    slog("player entity created");
    if(!plr) return;

    plr->sprite = gf2d_sprite_load_all(
        "images/ZeldaUp.png",
        32,
        32,
        1,
        0);
    
    plr->animated = 0;
    plr->dir = North;
    plr->shape = gfc_shape_circle(0,0,10);
    plr->drawOffset = vector2d(16,16);
    plr->think = player_think;
    plr->update = player_update;
    plr->currhealth = 6;
    plr->maxhealth = 6;

    data = gfc_allocate_array(sizeof(PlayerData), 1);        
    player_load(data);

    inv = gfc_allocate_array(sizeof(PlayerInv), 1);
    player_inv_load(inv);

    data->inv = inv;
    plr->data = data;
    

    vector2d_copy(plr->position, vector2d(data->xPos, data->yPos));

    bowSound = gfc_sound_load("sounds/sounds_select.wav", 50.0, -1);

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

    sj_object_get_value_as_int(playerInvObj, "selectedItem", &inv->selectedItem);
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
    if(!self) return;

    UserInput swapIntent = prepare_user_input();
    PlayerData *pd = plr->data;
    PlayerInv *inv = pd->inv;

    int prevItem = inv->selectedItem - 1;
    int nextItem = inv->selectedItem + 1;

    switch(self->dir)
    {
        case North:
            plr->sprite = gf2d_sprite_load_all(
            "images/ZeldaUp.png",
            32,
            32,
            1,
            0);
            break;

        case South:
            plr->sprite = gf2d_sprite_load_all(
            "images/ZeldaDown.png",
            32,
            32,
            1,
            0);
            break;

        case West:
            plr->sprite = gf2d_sprite_load_all(
            "images/ZeldaLeft.png",
            32,
            32,
            1,
            0);
            break;

        case East:
            plr->sprite = gf2d_sprite_load_all(
            "images/ZeldaRight.png",
            32,
            32,
            1,
            0);
            break;
    }
    if(swapCooldown <= 0)
    {
        if(swapIntent.QSL)
        {
            if(!(inv->selectedItem <= ItemEmpty))
            {
                switch (prevItem)
                {
                case ItemEmpty:
                    if(inv->hasBomb)
                        inv->selectedItem -= 1;
                    break;
                case ItemBomb:
                    if(inv->hasBomb)
                        inv->selectedItem -= 1;
                    break;
                
                case ItemBow:
                    if(inv->hasBow)
                        inv->selectedItem -= 1;

                case ItemCandle:
                    if(inv->hasCandle)
                        inv->selectedItem -= 1;
                default:
                    break;
                }
                swapCooldown = 30;
            }
        }
        else if (swapIntent.QSR)
        {
            if(!(inv->selectedItem >= ItemCandle))
            {
                switch (nextItem)
                {
                case ItemEmpty:
                    inv->selectedItem += 1;
                    break;
                
                case ItemBomb:
                    if(inv->hasBomb)
                        inv->selectedItem += 1;
                    break;
                
                case ItemBow:
                    if(inv->hasBow)
                        inv->selectedItem += 1;

                case ItemCandle:
                    if(inv->hasCandle)
                        inv->selectedItem += 1;
                default:
                    break;
                }
                swapCooldown = 30;
            }
        }
    }
    swapCooldown -= 1;
    
    if(swapIntent.Attack2)
    {
        player_attack2(self);
    }
}

void player_update(Entity *self)
{
    
    if (!self) return;
    UserInput moveIntent = prepare_user_input();
    PlayerData *pd = plr->data;

    pd->xPos = self->position.x;
    pd->yPos = self->position.y;
    
    
    if(moveIntent.Left)
    {
        self->velocity.x = -1 * moveIntent.Left * pd->speed;
        self->dir = West;
    }
    else if (moveIntent.Right)
    {
        self->velocity.x = moveIntent.Right * pd->speed;
        self->dir = East;
    }
    else
        self->velocity.x = 0;

    if(moveIntent.Up)
    {
        self->velocity.y = -1 * moveIntent.Up * pd->speed;
        self->dir = North;
    }
    else if (moveIntent.Down)
    {
        self->velocity.y = moveIntent.Down * pd->speed;
        self->dir = South;
    }
    else
        self->velocity.y = 0;

    camera_center_at(self->position);

}

void player_attack2(Entity *self)
{
    PlayerData *pd = plr->data;
    PlayerInv *inv = pd->inv;

    if(attack2Cooldown <= 0)
    {
        switch (inv->selectedItem)
        {
        case ItemBomb:
            //char *c = "images/item/bomb.png";   
            //projectile_new(self, self->dir, 0, 0, c);
            break;
        
        case ItemBow:
            char *a = "images/item/bolt.png";
            gfc_sound_play(bowSound, 0, 50.0, -1, -1);
            projectile_new(self, self->dir, 5.0, 3.0, a);
            break;
        case ItemCandle:
            char *b = "images/item/fire.png";
            projectile_new(self, self->dir, 1.5, 10, b);
            break;
        default:
            
            break;
        }
        attack2Cooldown = 30;
    }
    attack2Cooldown -= 1;
    

}

Vector2D player_get_position()
{
    return plr->position;
}

PlayerData* player_get_pd()
{
    return plr->data;
}

int player_get_curr_health()
{
    return plr->currhealth;
}

int player_get_max_health()
{
    return plr->maxhealth;
}

Shape player_get_shape()
{
    return entity_get_shape(plr);
    
}

void player_set_max_health(int increase)
{
    plr->maxhealth += increase;
}

void player_upgrade_sword_damage(int increase)
{
    PlayerData *pd = plr->data;
    pd->meleeMult += increase;
}

void player_upgrade_bow_damage(int increase)
{
    PlayerData *pd = plr->data;
    pd->arrowMult += increase;
}

void player_upgrade_speed(int increase)
{
    PlayerData *pd = plr->data;
    pd->speed += increase;
}

Entity* player_get_ent()
{
    return plr;
}