#include "id.h"
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <sys/types.h>


int new_id(void)
{
    static int id = 0;
    
    id += 1;
    return id;
}

static void handle_request(struct id_object_s *self, struct request_id_s *request,  world_t *informations)
{
    memcpy(&self->request, request, sizeof(self->request));
}

static void send_response(struct id_object_s* self, int udpfd)
{
    // __u_char digest[MD5_DIGEST_LENGTH];
    struct response_id_s response;
    memset(&response, 0, sizeof(struct response_id_s));
    response.type = ID;
    response.len = sizeof(response);
    response.body.id = self->client_id;

    char to_send[sizeof(response) + MD5_DIGEST_LENGTH] = {0};
    
    create_payload(to_send, &response, sizeof(struct response_id_s));

    sendto(udpfd, to_send, sizeof(to_send), 0, 
					get_client_socket(self->client), sizeof(struct sockaddr_in));

    self->destroy(self);
}

static void destroy_self(struct id_object_s* self)
{
    free(self);
}

type_object_t *create_id_object(int id, struct client *cli)
{
    struct id_object_s *object = malloc(sizeof(struct id_object_s));

    object->client_id = id;
    object->client = cli;
    // printf("new client %d\n", id);
    object->handle = &handle_request;
    object->response = &send_response;
    object->destroy = &destroy_self;
    return (type_object_t*)object;
}