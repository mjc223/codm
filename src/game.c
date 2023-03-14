#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

#include "codm_entity.h"
#include "codm_player.h"
#include "codm_input.h"
#include "codm_hud.h"

#include "codm_camera.h"
#include "codm_level.h"

void enemy_think(Entity *self);

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    Level *level;
    const Uint8 * keys;
    Sprite *sprite;
    Entity *ent;

    entity_manager_init(1024);

    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Color mouseColor = gfc_color8(1,1,255,200);
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0); 
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16,0);

    level = level_load("config/test.level");
    level_set_active_level(level);

    
    ent = entity_new();
    if(ent) //if creation valid
    {
        slog("Valid entity created"); 
        ent->shape = gfc_shape_circle(0,0,10);
        ent->sprite = gf2d_sprite_load_all(
            "images/space_bug_top.png",
            128,
            128,
            16,
            0);
        ent->think = enemy_think;
        ent->position = vector2d(90, 90);
        ent->drawOffset = vector2d(64,64);
    }
    

    player_init(vector2d(100,100));

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/

        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;

        entity_think_all();
        entity_update_all();
        camera_world_snap();
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));

            level_draw(level_get_active_level());
            entity_draw_all();
        

            user_input_update();

            //UI elements last
            hud_update_all();
            
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);

        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }

    level_free(level);
    entity_free(ent);

    slog("---==== END ====---");
    return 0;
}

void enemy_think(Entity *self)
{
    if(!self) return;

    float speed = gfc_random() * 2 + 1;

    if(self->position.x >= 500) 
        self->velocity.x = -1 * speed;
    else if (self->position.x <= 0)
        self->velocity.x = 1 * speed;
    
    if(self->position.y >= 300) 
        self->velocity.y = -1 * speed;
    else if (self->position.y <= 0)
        self->velocity.y = 1 * speed;
    
}
/*eol@eof*/
