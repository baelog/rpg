
#ifndef PLAYER_H_
#define PLAYER_H_

#include "protocol/types.h"

player_t *get_player_by_id(int client_id, world_t *player_list);
player_t *get_player_list(world_t *infos);

#endif /* !PLAYER_H_ */
