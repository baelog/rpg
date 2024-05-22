
#ifndef CLIENT_H_
#define CLIENT_H_

#include <SFML/System/Clock.h>
#include "../protocol/types.h"

typedef struct response_s response_t; 
typedef struct request_s request_t;
typedef struct tiles_s tiles_t;
typedef struct player_s player_t;
typedef struct sockaddr sockaddr;

#define VISION_SIZE 30

typedef struct waiting_request_s {
    request_t *request;
    struct waiting_request_s *next;
    sfClock *clock;
}waiting_request_t;


struct client_information {
    tiles_t *scene_object[VISION_SIZE];
    player_t *players[VISION_SIZE];
    waiting_request_t *requests;
    int player_id;
};

struct thread_args {
    struct client_information* client_informations;
    int sockfd;
    struct sockaddr_in *servaddr;
};

enum move {
    UP = 1,
    RIGHT = 2,
    DOWN = 4,
    LEFT = 8
};

int new_request(struct sockaddr *server, int fd, waiting_request_t **request_list, void *information, int type);
request_t *create_action_request(struct sockaddr *server, int udpfd, void *value);
void create_tiles(tiles_t **array, player_t **players, IResponse *response);
// void create_tiles(tiles_t **array, IResponse *response);
int get_message(char *buffer, int sockfd, struct sockaddr *servaddr);
int waiting_answer(char* buffer, int fd, struct sockaddr *servaddr, struct client_information *client_infos);
#endif /* !CLIENT_H_ */
