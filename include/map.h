/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** map
*/

#ifndef MAP_H_
#define MAP_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>

enum tiles {
    VOID,
    WALL,
    GROUND,
    PLAYER //TODO change
};

typedef struct tiles_s{
    sfVector2f position;
    sfSprite *spirte;
    void (*print)(struct tiles_s*, sfRenderWindow*);
    void *on_colide;
    void *on_destroy;
}tiles_t;

tiles_t *create_ground(sfVector2f);
tiles_t *create_wall(sfVector2f);

tiles_t ***create_scene_object(grid_t);

#endif /* !MAP_H_ */
