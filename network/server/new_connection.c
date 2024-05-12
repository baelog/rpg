#include "server.h"
#include <arpa/inet.h>
#include "../../include/map.h"
#include <string.h>

static void on_colide(void) {

}

static void on_destroy(void) {

}

int create_player(player_t new_player, tiles_t ***map, int id)
{
    new_player.id = id;
    new_player.on_colide = &on_colide;
    new_player.on_destroy = &on_destroy;

    for (int i = 0; map[i]; i++)
        for (int j = 0; map[i][j]; j++)
            if (map[i][j]->spawn) {
                memcpy(&new_player.position, &map[i][j]->position, sizeof(map[i][j]->spawn));
                return 0;
            }
    new_player.position = (sfVector2f){0, 0};
    return 1;
}

struct client *new_client(struct sockaddr_in client, world_t *world_information)
{
	static int client_id = 0;

	struct client *new_client = malloc(sizeof(struct client));
	struct sockaddr_in *new = malloc(sizeof(struct sockaddr_in));

	memcpy(new, &client, sizeof(client));
	new_client->socket = new;
	new_client->id = client_id++;

    create_player(world_information->player[client_id - 1], world_information->map, client_id);
    world_information->player_count++;

	return new_client;
}