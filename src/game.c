#include <SDL.h>
#include <SDL_ttf.h>

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "gf2d_font.h"
#include "gfc_audio.h"

#include "codm_entity.h"
#include "codm_player.h"
#include "codm_input.h"
#include "codm_hud.h"
#include "codm_object.h"

#include "codm_camera.h"
#include "codm_item.h"
#include "codm_level.h"
#include "codm_npc.h"
#include "codm_enemy.h"

Sound* gameMusic;


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    Level *level;
    const Uint8 * keys;
    Sprite *sprite;
    int mainMenu = 1;

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
    gf2d_font_init("config/font.cfg");


    gfc_audio_init(256,16,4,1,1,1);
    gameMusic = gfc_sound_load("music/wisdom.mp3", 50.0, -1);
    gfc_sound_play(gameMusic, -1, 30.0, -1, -1);

    //Main Menu
    while(mainMenu == 1)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        if (keys[SDL_SCANCODE_RETURN])mainMenu = 0;

        sprite = gf2d_sprite_load_image("images/backgrounds/bg_title.png");

        camera_world_snap();
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));

            gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }

    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/background2.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16,0);

    level = level_load("config/test.level");
    level_set_active_level(level);

    

    health_upgrade_init(vector2d(300, 300));
    sword_upgrade_init(vector2d(450, 450));
    bow_upgrade_init(vector2d(500, 500));
    speed_upgrade_init(vector2d(500, 200));
    warp_init(vector2d(600, 520));
    key_init(vector2d(100, 100));

    
    eye_switch_init(vector2d(100, 450), wall_trigger_init(vector2d(100, 350)));
    trick_wall_init(vector2d(100, 550));
    lock_init(vector2d(100, 850));
    push_block_init(vector2d(100, 650));

    player_init(vector2d(100,100));
    hud_init();

    npc_init(vector2d(550, 350), 10);
    npc_init(vector2d(775, 650), 11);
    sword_init(vector2d(775, 750));

    turret_init(vector2d(700, 250));
    octopus_init(vector2d(850, 300));
    worm_init(vector2d(1500, 450));
    bird_init(vector2d(1600, 550));

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
    slog("---==== END ====---");
    return 0;
}


void new_level_load(char *newLevelPath)
{
    Level *level;
    level = level_load(newLevelPath);

    level_set_active_level(level);
}
/*eol@eof*/
