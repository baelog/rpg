
#ifndef ID_H_
#define ID_H_

#include "types.h"
// #include <openssl/md5.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int cipher(void *data, size_t size, __u_char *digest);
int create_payload(char *payload, void *request, int offset);

struct response_id_s {
    int len;
    int type;
    Response_body body;
};

struct request_id_s {
    int len;
    int type;
    Request_body body;
};

struct id_object_s {
    int client_id;
    void (*handle)(struct id_object_s*, struct request_id_s*, struct sockaddr_in*);
    void (*response)(struct id_object_s* self, int fd);
    void (*destroy)(struct id_object_s*);
    struct sockaddr_in *client;
    struct request_id_s request; 
};

#endif /* !ID_H_ */
