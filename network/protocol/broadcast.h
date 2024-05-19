#include "types.h"
#include <stdlib.h>

#define MD5_DIGEST_LENGTH 16
#define VISION_LENGHT 100

int cipher(void *data, size_t size, unsigned char *digest);
int create_payload(char *payload, void *request, int offset);

struct response_broadcast_s {
    int len;
    int type;
    int request_id;
    Response_body body;
};

typedef struct world_s world_t;
void player_vision();

// void send(struct sockaddr_in *client, int client_id, world_t* map, int fd);
