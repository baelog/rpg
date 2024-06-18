

#ifndef SERVER_H_
#define SERVER_H_

// #include "protocol/types.h"
#include <SFML/System/Vector2.h>
#include <SFML/System/Clock.h>
#include <openssl/md5.h>
#include "../protocol/types.h"

#define VISION_SIZE 30
#define MAX_CLIENTS 10

typedef struct world_s world_t;

// typedef union {
//     int value;
//     sfVector2f vector;
// }Request_body;

// typedef union {
//     int id;
//     struct vision_s object[VISION_SIZE];
// }Response_body;

// enum type {
//     BROADDCAST,
//     ID,
//     POSITION,
//     INVENTARY,
//     ACTIONS,
//     ERROR
// };

struct request_s {
    int len;
    int type;
    int request_id;
    Request_body body;
};

struct response_s {
    int len;
    int type;
    int request_id;
    Response_body body;
};

struct client {
    int id;
    int state;
    int prev_state;
    struct sockaddr_in *socket;
    sfClock *clock;
};

typedef struct server_information_s {
    sfClock *clock;
    struct client *client_list[MAX_CLIENTS + 1];
} server_information_t;

struct type_object_s {
    int client_id;
    void (*handle)(struct type_object_s *self, struct request_s*, world_t *informations);
    void (*response)(struct type_object_s* self, int fd);
    void (*destroy)(struct type_object_s*);
};

int cipher(void *data, size_t size, char *digest);

world_t *instanciate_file(char *file);

void broadcast(struct sockaddr_in *client, int client_id, world_t* map, int fd);
struct type_object_s *create_id_object(int, struct client *cli);
type_object_t *create_action_object(int id, struct client *cli);
struct client *new_client(struct sockaddr_in client, world_t *world_information);

#endif /* !SERVER_H_ */
