#include "../include/map.h"
#include <string.h>

player_t *get_player_by_id(int client_id, world_t *infos)
{
    for (int i = 0; infos->player[i].id && i != MAX_PLAYER; i++) {
        if (infos->player[i].id == client_id) {
            return (&infos->player[i]);
        }
    }
    return &infos->player[0];
}

player_t *get_player_list(world_t *infos)
{
    return infos->player;
}