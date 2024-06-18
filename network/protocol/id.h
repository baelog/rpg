
#ifndef ID_H_
#define ID_H_

#include "types.h"
// #include <openssl/md5.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct sockaddr_in sockaddr_in;

int cipher(void *data, size_t size, __u_char *digest);
int create_payload(char *payload, void *request, int offset);

struct response_id_s {
    int len;
    int type;
    int request_id;
    Response_body body;
};

struct request_id_s {
    int len;
    int type;
    int request_id;
    Request_body body;
};

struct id_object_s {
    int client_id;
    void (*handle)(struct id_object_s*, struct request_id_s*, world_t *informations);
    void (*response)(struct id_object_s* self, int fd);
    void (*destroy)(struct id_object_s*);
    struct client *client;
    struct request_id_s request; 
};

struct sockaddr *get_client_socket(struct client *cli);
int get_client_id(struct client *cli);
int get_client_state(struct client *cli);

#endif /* !ID_H_ */
