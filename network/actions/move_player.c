#include <SFML/System/Vector2.h>
#include "../../include/map.h"
#include <math.h>

int move_player(player_t *player, int value)
{
    sfVector2f direction = {0, 0};
    double speed = .8;
    double m;

    if (value & 1)
        direction.x = 1;
    if (value & 2)
        direction.y = 1;
    if (value & 4)
        direction.x = -1;
    if (value & 8)
        direction.y = -1;
    
    m = sqrt(direction.x * direction.x + direction.y * direction.y);
    player->position.x = direction.x / m * speed;
    player->position.y = direction.y / m * speed;
}