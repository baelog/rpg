

#ifndef SERVER_H_
#define SERVER_H_

// #include "protocol/types.h"
#include <SFML/System/Vector2.h>
#include <openssl/md5.h>

typedef struct world_s world_t;

typedef union {
    int value;
    sfVector2f vector;
}Request_body;

typedef union {
    int id;
    sfVector2f position;
}Response_body;

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

int cipher(void *data, size_t size, __u_char *digest);

world_t *instanciate_file(char *file);

struct type_object_s *create_id_object(int);

struct type_object_s *(*const create_object[])(int) = {
    &create_id_object,
    &create_id_object
};

#endif /* !SERVER_H_ */
