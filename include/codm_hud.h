#ifndef __CODM_HUD_H__
#define __CODM_HUD_H__

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gf2d_font.h"
#include "gfc_vector.h"

#include "codm_player.h"

void hud_init();

void hud_update_all();

void hud_update_player_info();

void hud_change_message(char *message);

void hud_update_message(char *message);

void hud_update_stats();

#endif