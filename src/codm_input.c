#include <SDL.h>
#include "simple_logger.h"

#include "codm_input.h"
//#include <codm_player.h>

typedef struct
{
    int Up;
    int Down;
    int Left;
    int Right;

    int Attack1;
    int Attack2;

    int QSL;
    int QSR;

    int Menu;
}UserInput;

static UserInput user_input = {0};
static int SHOW_INPUT = 0;

void read_scan_code()
{
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); 

    if (keys[SDL_SCANCODE_UP]) user_input.Up = 1; else user_input.Up = 0;
    if (keys[SDL_SCANCODE_DOWN]) user_input.Down = 1; else user_input.Down = 0;
    if (keys[SDL_SCANCODE_LEFT]) user_input.Left = 1; else user_input.Left = 0;
    if (keys[SDL_SCANCODE_RIGHT]) user_input.Right = 1; else user_input.Right = 0;

    if (keys[SDL_SCANCODE_Z]) user_input.Attack1 = 1; else user_input.Attack1 = 0;
    if (keys[SDL_SCANCODE_X]) user_input.Attack2 = 1; else user_input.Attack2 = 0;

    if (keys[SDL_SCANCODE_Q]) user_input.QSL = 1; else user_input.QSL = 0;
    if (keys[SDL_SCANCODE_E]) user_input.QSR = 1; else user_input.QSR = 0;

    if (keys[SDL_SCANCODE_RETURN]) user_input.Menu = 1; else user_input.Menu = 0;
}

void sanitize_user_input()
{
    if(user_input.Up && user_input.Down)        {user_input.Up = 0; user_input.Down = 0;}
    if(user_input.Left && user_input.Right)     {user_input.Left = 0; user_input.Right = 0;}

    if((user_input.Up || user_input.Down) && (user_input.Left || user_input.Right)) 
        {user_input.Left = 0; user_input.Right = 0;}

    if(user_input.QSL && user_input.QSR)        {user_input.QSL = 0; user_input.QSR = 0;}
}

Vector2D prepare_user_input()
{
    if (SHOW_INPUT) slog("\n Left: %i, Right: %i, Up: %i, Down: %i \n Attack1: %i, Attack2: %i \n QSL: %i, QSR: %i \n Menu: %i",
    user_input.Left, user_input.Right, user_input.Up, user_input.Down, user_input.Attack1, user_input.Attack2, 
    user_input.QSL, user_input.QSR, user_input.Menu);

    int HORIZONTAL, VERTICAL;
    if(user_input.Left)
        HORIZONTAL = -1;
    else if (user_input.Right)
        HORIZONTAL = 1;
    else
        HORIZONTAL = 0;

    if(user_input.Up)
        VERTICAL = -1;
    else if (user_input.Down)
        VERTICAL = 1;
    else
        VERTICAL = 0;

    Vector2D vect = vector2d(HORIZONTAL,VERTICAL);

}

void user_input_update()
{
    read_scan_code();
    sanitize_user_input();
    //prepare_user_input();
}