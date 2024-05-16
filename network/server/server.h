

#ifndef SERVER_H_
#define SERVER_H_

// #include "protocol/types.h"
#include <SFML/System/Vector2.h>
#include <openssl/md5.h>
#include "../protocol/types.h"

#define VISION_SIZE 30

typedef struct world_s world_t;

// typedef union {
//     int value;
//     sfVector2f vector;
// }Request_body;

// typedef union {
//     int id;
//     struct vision_s object[VISION_SIZE];
// }Response_body;

enum type {
    BROADDCAST,
    ID,
    POSITION,
    INVENTARY,
    ACTIONS,
    ERROR
};

struct request_s {
    int len;
    int type;
    Request_body body;
};

struct response_s {
    int len;
    int type;
    Response_body body;
};

struct client {
    int id;
    struct sockaddr_in *socket;
};

struct type_object_s {
    int client_id;
    void (*handle)(struct type_object_s *self, struct request_s*, struct sockaddr_in*);
    void (*response)(struct type_object_s* self, int fd);
    void (*destroy)(struct type_object_s*);
};

int cipher(void *data, size_t size, char *digest);

world_t *instanciate_file(char *file);

void broadcast(struct sockaddr_in *client, int client_id, world_t* map, int fd);
struct type_object_s *create_id_object(int);
struct client *new_client(struct sockaddr_in client, world_t *world_information);

#endif /* !SERVER_H_ */
