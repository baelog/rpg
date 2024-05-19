#include "../include/map.h"

player_t *get_player_by_id(int client_id, world_t *infos)
{
    for (int i = 0; i != MAX_PLAYER; i++)
        if (infos->player[i].id == client_id) {
            return (&infos->player[i]);
        }
}