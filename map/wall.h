/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** wall
*/

#ifndef WALL_H_
#define WALL_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Sprite.h>

typedef struct tiles_s tiles_t;

struct wall_s{
    sfVector2f position;
    sfSprite *spirte;
    void (*print)(void);
    void *on_colide;
    void *on_destroy;
};

#endif /* !WALL_H_ */
