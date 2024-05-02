/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** ground
*/

#ifndef GROUND_H_
#define GROUND_H_

#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Types.h>

typedef struct tiles_s tiles_t;

struct ground_s{
    sfVector2f position;
    sfSprite *spirte;
    void (*print)(void);
    void *on_colide;
    void *on_destroy;
};


#endif /* !GROUND_H_ */
