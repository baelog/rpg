#include "broadcast.h"
#include <arpa/inet.h>
#include "../../include/map.h"
#include <string.h>
#include <unistd.h>

int is_in_range(sfVector2f v1, sfVector2f v2)
{
    //TODO CHANGE THE ARCODED CENTER OF POINT
    double vx = v1.x - v2.x + 25; 
    double vy = v1.y - v2.y + 25;

    return (((vx * vx) + (vy * vy)) < 10000);
}

void player_vision(tiles_t ***map, player_t *player, Response_body *response_body, player_t *player_list, int nb_player)
{
    int i = 0;
    for (int j = 0; j != nb_player; j++) {
        response_body->object[i].position = player_list[j].position;
        response_body->object[i].player_type = player->id == player_list[j].id ? 0 : player->id;
        response_body->object[i].type = 0;
        i++;
    }
    for (int j = 0; map[j]; j++) {
        for (int k = 0; map[j][k]; k++) {
            if (is_in_range(map[j][k]->position, player->position)) {
                response_body->object[i].position = map[j][k]->position;
                response_body->object[i].type = map[j][k]->get_type();
                response_body->object[i].player_type = 0;
                i++;
            }
        }
    }
    while (i < VISION_SIZE) {
        response_body->object[i].type = -1;
        i++;
    }
}


player_t get_player_position(int client_id, player_t *player_list)
{
    for (int i = 0; i != MAX_PLAYER; i++)
        if (player_list[i].id == client_id) {
            return (player_list[i]);
        }
}

void broadcast(struct sockaddr_in *client, int client_id, world_t* map, int fd)
{
    player_t player = get_player_position(client_id, map->player);
    struct response_id_s response;
    memset(&response, 0, sizeof(struct response_id_s));
    response.type = BROADDCAST;
    response.len = sizeof(response);

    char to_send[sizeof(response) + MD5_DIGEST_LENGTH] = {0};
    player_vision(map->map, &player, &response.body, map->player, map->player_count);
    create_payload(to_send, &response, sizeof(struct response_id_s));

    sendto(fd, to_send, sizeof(to_send), 0, 
					(struct sockaddr*)client, sizeof(struct sockaddr_in));

}