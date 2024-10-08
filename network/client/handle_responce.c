#include "../protocol/IResponse.h"
#include "../../include/map.h"
#include "../player.h"
#include "client.h"
#include "../actions/all_action.h"
// #include <unistd.h>
#include <stdio.h>
#include "../tools.h"

void create_tiles(tiles_t **array, player_t **players, IResponse *response)
{
	tiles_t *(*backgroundConstructor[]) (sfVector2f) = {
		&create_ground, //TODO create the void finction
		&create_wall,
		&create_ground
	};
	player_t *(*create_players[]) (sfVector2f, int) = {
		&create_other_player,
		&create_me
	};
	int j = 0;
	int k = 0;

	#ifdef _WIN32
		WaitForSingleObject(lock, INFINITE);
	#else
		pthread_mutex_lock(&lock);
	#endif

	for (int i = 0; i != VISION_SIZE && response->body.object[i].type >= 0; i++) {
		if (!response->body.object[i].type) {
			players[k++] = create_players[response->body.object[i].player_type == 0](response->body.object[i].position, response->body.object[i].player_type);
			// printf("player: %d %f %f\n", response->body.object[i].player_type, response->body.object[i].position.x, response->body.object[i].position.y);
		}
		if (response->body.object[i].type) {
			// printf("not my type ? %d\n", response->body.object[i].type);
			array[j++] = backgroundConstructor[response->body.object[i].type](response->body.object[i].position);
		}
	}
	
	#ifdef _WIN32
		ReleaseMutex(lock);
	#else
		pthread_mutex_unlock(&lock); 
	#endif
	
	while (j < VISION_SIZE)
		array[j++] = NULL;
}

int waiting_answer(char* buffer, int fd, struct sockaddr *servaddr, struct client_information *client_infos)
{
    int is_valide = 0;
    if (/*!usleep(100000) ||*/ (is_valide = get_message(buffer, fd, servaddr))) {
        if (!is_valide)
            return 0;
        // printf("je suis dans cette boucle\n");
        struct IResponse *response = (struct IResponse*)buffer;
        if (response->type == BROADDCAST)
            create_tiles(client_infos->scene_object, client_infos->players, response);
        if (response->type == ACTIONS) {
            // player_t *player = get_player_by_id(client_infos->player_id, infos);
            // move_player(player, response->body->)
			printf("je detect la requete\n");
	
        }
    }
}

// void create_tiles(tiles_t **array, struct response_id_s *response)