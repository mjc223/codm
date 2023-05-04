#ifndef __CODM_ENTITY_H__
#define __CODM_ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf2d_sprite.h"

#include "gfc_shape.h"

typedef enum ItemType{HealthUp, SpeedUp, SwordUp, BowUp, CandleUp, BombAmmo, ArrowAmmo, EyeSwitch, Living, Projectile, Warp, Key, Sword}ItemType;
typedef enum FacingDirection{North, South, East, West}FacingDirection;

typedef struct Entity_S
{
    Bool _inuse;
    Sprite *sprite;
    int id;

    int currhealth;
    int maxhealth;

    int animated;
    int frameCount;
    
    float frame;
    float rotation;
    FacingDirection dir;
    float speed;

    Vector2D drawOffset;

    Shape shape;

    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    ItemType type;

    float damage;
    char *info;

    void (*think) (struct Entity_S *self);
    void (*update) (struct Entity_S *self);
    void (*draw) (struct Entity_S *self);
    void (*free_entity) (struct Entity_S *self);
    void *data;
}Entity;

/**
 * @brief initialize internal manager for entity system
 * automatically queue up the the close function for program exit
 * @param max maximum number of supported entities at a given time
*/
void entity_manager_init(Uint32 max);

/**
 * @brief allocate and initialize a new entity
 * @return NULL if there are no entities left, an empty entity otherwise
*/
Entity *entity_new();

/**
 * @brief Close the entity manager and remove it from memory,
*/
void entity_manager_close();

/**
 * @brief Free a single entity, remove it from the entity list, and
 * release it from memory
 * @param ent entity to be freed/removed
*/
void entity_free(Entity *ent);

/**
 * @brief Calls entity_free, frees all not in use entities
*/
void entity_free_all();

void entity_clear_all();

/**
 * @brief Draw a single entity
 * @param ent Entity to be rendered
*/
void entity_draw(Entity *ent);

/**
 * @brief Draw all relevant entities
*/
void entity_draw_all();

/**
 * @brief Call the think function for all avaiable entities
*/

void entity_think_all();

/**
 * @brief Call the update function for all available entities
*/
void entity_update_all();

/**
 * @brief given an entity get its shape in world space
 * @param ent the entity to check
 * @return a shape where its position is set to the world position
 */

Shape entity_get_shape(Entity *ent);

/**
 * @brief given an entity get its shape in world space where it will be after it moves
 * @param ent the entity to check
 * @return a shape where its position + velocity is set to the world position
 */

Shape entity_get_shape_after_move(Entity *ent);

Entity* get_entity_list();
int get_entity_max();

void entity_damage(int damage);

#endif