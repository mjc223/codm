#ifndef __CODM_PLAYER_H__
#define __CODM_PLAYER_H__

#include "gfc_vector.h"
#include "simple_json.h"
#include "codm_entity.h"

typedef struct
{
    int hasBomb;
    int hasBow;
    int hasCandle;
}PlayerInv;

typedef struct
{
    float xPos;
    float yPos;

    int speed;

    int meleeMult;
    int arrowMult;
    int attackSpeed;

    int currBomb;
    int maxBomb;

    int currArrow;
    int maxArrow;

    PlayerInv* inv;
}PlayerData;


void player_init(Vector2D position);

void player_think(Entity *self);

void player_update(Entity *self);

void player_load(PlayerData *data);

void player_inv_load(PlayerInv *inv);

void player_save();

SJson* player_save_writer();

Vector2D player_get_position(Entity *self);

int player_get_curr_health();

PlayerData* player_get_pd();

#endif