#include "server.h"
#include <arpa/inet.h>
#include "../../include/map.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void on_colide(void) {

}

static void on_destroy(void) {

}

int create_player(player_t **new_player, tiles_t ***map, int id)
{
    for (int i = 0; map[i]; i++) {
        for (int j = 0; map[i][j]; j++) {
            // printf("je tourne\n");
            if (map[i][j]->spawn) {
                // printf("ici la victoire %f, %f\n", map[i][j]->position.x, map[i][j]->position.y);
                *new_player = create_me((sfVector2f){map[i][j]->position.x, map[i][j]->position.y}, id);
                // new_player->position = (sfVector2f){map[i][j]->position.x, map[i][j]->position.y};
                return 0;
            }
        }
    }
    *new_player = create_me((sfVector2f){0, 0}, id);

    // new_player->position = (sfVector2f){0, 0};
    return 1;
}

struct client *new_client(struct sockaddr_in client, world_t *world_information)
{
	static int client_id = 1;

	struct client *new_client = malloc(sizeof(struct client));
	struct sockaddr_in *new = malloc(sizeof(struct sockaddr_in));

	memcpy(new, &client, sizeof(client));
	new_client->socket = new;
	new_client->id = client_id++;
    new_client->state = 0;
    new_client->prev_state = 0;

    create_player(&world_information->player[new_client->id - 1], world_information->map, new_client->id);
    // printf("player posion at spawn %f %f\n", world_information->player[client_id - 1].position.x, world_information->player[client_id - 1].position.y);
    world_information->player_count++;

	return new_client;
}