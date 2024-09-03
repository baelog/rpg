#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../player.h"
#include "../../include/map.h"

void update_players_positions(world_t *map)
{
    for (int i = 0; i < map->player_count; i++) {
        map->player[i]->move(map->player[i]);
    }
}