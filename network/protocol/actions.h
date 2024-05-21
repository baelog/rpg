
#ifndef ACTIONS_H_
#define ACTIONS_H_

#include "types.h"

int generate_request_id(void);
int create_payload(char *payload, void *request, int offset);

typedef struct waiting_request_s waiting_request_t;
typedef struct sockaddr_in sockaddr_in;
struct response_actions_s {
    int len;
    int type;
    int request_id;
    Response_body body;
};

struct request_actions_s {
    int len;
    int type;
    int request_id;
    Request_body body;
};

struct actions_object_s {
    int client_id;
    void (*handle)(struct actions_object_s*, struct request_actions_s*, struct sockaddr_in*, world_t *informations);
    void (*response)(struct actions_object_s* self, int fd);
    void (*destroy)(struct actions_object_s*);
    struct sockaddr_in *client;
    struct request_actions_s request;
    int request_id;
};

int move_player(player_t *player, int value);
void remove_request(struct waiting_request_s **list, struct waiting_request_s *ptr);

#endif /* !ACTIONS_H_ */
