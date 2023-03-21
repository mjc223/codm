#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "simple_logger.h"

#include "gfc_vector.h"
#include "gf2d_sprite.h"


#include "codm_hud.h"
#include "codm_player.h"   




//Retrieve Player Data, Draw relevant Player Data
char *currMessage;
enum InventoryOrder {ItemEmpty, ItemBomb, ItemBow, ItemCandle}; 

Sprite *bomb, *bow, *candle;

void hud_init()
{
    bomb = gf2d_sprite_load_all("images/item/bomb.png",16,8,1,0);
    bow = gf2d_sprite_load_all("images/item/bow.png",16,8,1,0);
    candle = gf2d_sprite_load_all("images/item/candle.png",16,8,1,0);

    //gf2d_sprite_draw_image(bomb,vector2d(600,800));
}

void hud_update_all()
{
    hud_update_player_info();
    hud_update_stats();
    hud_update_message(currMessage);
}

void hud_update_player_info()
{
    Rect pos;
    char buf[15];
    SDL_snprintf(buf, sizeof(buf), "Health: %i", player_get_max_health());
    pos = gf2d_font_get_text_wrap_bounds_tag(buf, FT_Normal, 600, 200);
    gf2d_font_draw_text_wrap_tag(buf, FT_Normal, GFC_COLOR_WHITE, pos);
}

void hud_change_message(char *a)
{
    currMessage = a;
}

void hud_update_message(char *a)
{
    if (!a) return;
    Rect message;
    message = gf2d_font_get_text_wrap_bounds_tag(a, FT_Normal, 300, 800);
    message.x = message.x + 650.0;

    gf2d_font_draw_text_wrap_tag(a, FT_Normal, GFC_COLOR_RED, message);
}

void hud_update_stats()
{
    PlayerData* pd = player_get_pd();
    PlayerInv *inv = pd->inv;
    
    Rect pos;
    char buf[50];

    SDL_snprintf(buf, sizeof(buf), "XPos: %f,   YPos: %f", pd->xPos, pd->yPos);
    pos = gf2d_font_get_text_wrap_bounds_tag(buf, FT_Normal, 600, 200);
    pos.y = pos.y + 600.0;

    gf2d_font_draw_text_wrap_tag(buf, FT_Normal, GFC_COLOR_WHITE, pos);

    int i = (int) inv->selectedItem;
    char *a;
    switch (i)
    {
    case ItemEmpty:
        a = "Empty";
        break;

    case ItemBomb:
        a = "Bomb";
        break;
    
    case ItemBow:
        a = "Bow";
        break;

    case ItemCandle:
        a = "Candle";
        break;
    default:
        break;
    }

    Rect item;
    char buf2[15];
    
    
    
    SDL_snprintf(buf2, sizeof(buf2), "Value: %s", a);
    item = gf2d_font_get_text_wrap_bounds_tag(buf2, FT_Normal, 600, 200);
    item.y = item.y + 600.0;
    item.x = item.x + 600.0;

    gf2d_font_draw_text_wrap_tag(buf2, FT_Normal, GFC_COLOR_WHITE, item);

    //gf2d_sprite_draw_image(s,vector2d(0,0));
}
