#include <SFML/System/Vector2.h>
#include "../../include/map.h"
#include <math.h>
#include <stdio.h>

int move_player(player_t *player, int value)
{
    sfVector2f direction = {0, 0};
    double speed = .8;
    double m;

    if (!value)
        return 0;
    if (value & 1)
        direction.x = 1;
    if (value & 2)
        direction.y = 1;
    if (value & 4)
        direction.x = -1;
    if (value & 8)
        direction.y = -1;
    
    // printf("%f, %f\n", player->position.y, player->position.x);
    m = sqrt(direction.x * direction.x + direction.y * direction.y);
    player->position.x += (direction.x / m) * speed;
    player->position.y += (direction.y / m) * speed;

    // printf("%f, %f, %f\n", player->position.y, player->position.x, m);
    return 0;
}