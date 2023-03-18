#include "codm_hud.h"
#include "codm_player.h"   
#include <SDL_ttf.h>
#include "simple_logger.h"
#include <stdio.h>

//Retrieve Player Data, Draw relevant Player Data

void hud_update_all()
{
    hud_update_player_info();
    hud_update_message();
}

void hud_update_player_info()
{
    PlayerData* pd = player_get_pd();
    Rect pos;
    char buf[50];
    SDL_snprintf(buf, sizeof(buf), "XPos: %f,   YPos: %f", pd->xPos, pd->yPos);
    //slog(buf);
    //gfc_line_sprintf("XPos: %f,      YPos: %f", pd->xPos, pd->yPos);
    
    

    pos = gf2d_font_get_text_wrap_bounds_tag(buf, FT_Normal, 600, 200);
    gf2d_font_draw_text_wrap_tag(buf, FT_Normal, GFC_COLOR_WHITE, pos);
}

void hud_update_message()
{
    //Rect message;
    //message = gf2d_font_get_text_wrap_bounds_tag("A Potential message", FT_Normal, 300, 800);
    //gf2d_font_draw_text_wrap_tag("A Potential message", FT_Normal, GFC_COLOR_BLACK, message);
}
