#include "../include/map.h"
#include <string.h>

player_t *get_player_by_id(int client_id, world_t *infos)
{
    for (int i = 0; infos->player[i]->id && i <= infos->player_count; i++) {
        if (infos->player[i]->id == client_id) {
            return (infos->player[i]);
        }
    }
    return *(infos->player);
}

player_t *get_player_list(world_t *infos)
{
    return infos->player;
}

void set_player_state(player_t *player, int state, int mask)
{
    player->state &= ~mask;
    player->state |= state;
}

void update_player_position(player_t *player)
{
    player->move(player);
}