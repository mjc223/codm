#include <SDL.h>
#include "simple_logger.h"
#include "gfc_vector.h"
//#include <codm_player.h>

typedef struct UserInput
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

/**
 * @brief Reads SDL ScanCodes into UserInput struct
*/
void read_scan_code();

/**
 * @brief Sanitizes UserInput struct to prevent SOCD and diagonal inputs
*/
void sanitize_user_input();

/**
 * @brief Prepares UserInput struct for Player control functions
*/
UserInput prepare_user_input();

/**
 * @brief Calls necessary functions to evaluate user input
*/
void user_input_update();