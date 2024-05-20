#include "actions.h"
#include "../tools.h"
#include <openssl/md5.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../player.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


request_t *create_action_request(struct sockaddr *server, int udpfd, void *value)
{
    // __u_char digest[MD5_DIGEST_LENGTH];
    int *action = (int*)value;
    struct request_actions_s *request = malloc(sizeof(struct request_actions_s));
    
    memset(request, 0, sizeof(struct request_actions_s));
    
    request->type = ACTIONS;
    request->len = sizeof(struct request_actions_s);
    request->request_id = generate_request_id();
    printf("value send %d \n", *action & 0xff);
    request->body.value = *action & 0xff;
    // printf("int %d\n", request->type);

    char to_send[sizeof(*request) + MD5_DIGEST_LENGTH] = {0};
    
    create_payload(to_send, request, sizeof(*request));

    // struct request_actions_s *request2 = (struct request_actions_s *)to_send;
    // printf("value send bis %d \n", request2->body.value);

    sendto(udpfd, to_send, sizeof(to_send), 0, 
					server, sizeof(struct sockaddr));

    return (request_t *)request;
}

void read_response(char *buffer, struct waiting_request_s **list)
{
    struct response_actions_s *response = malloc(sizeof(struct response_actions_s));
    memcpy(response, buffer, sizeof(struct response_actions_s));
    
    struct waiting_request_s *ptr = (struct waiting_request_s *)find_id((struct list_s *)*list, response->request_id);
    remove_request(list, ptr);
}


static void handle_request(struct actions_object_s *self, struct request_actions_s *request, struct sockaddr_in *client, world_t *informations)
{
    memcpy(&self->request, request, sizeof(self->request));
    player_t *player = get_player_by_id(self->client_id, informations);
    // printf("%f, %f\n", player->position.y, player->position.x);
    printf("%d value request\n", self->request.body.value);
    move_player(player, self->request.body.value);

    // printf("%f, %f\n", player->position.y, player->position.x);
    self->client = client;
    self->request_id = request->request_id;
}

static void send_response(struct actions_object_s* self, int udpfd)
{
    struct response_actions_s response;
    memset(&response, 0, sizeof(struct response_actions_s));
    response.type = ACTIONS;
    response.len = sizeof(response);
    response.body.id = 1;
    response.request_id = self->request_id;

    char to_send[sizeof(response) + MD5_DIGEST_LENGTH] = {0};
    
    memset(to_send, 0, sizeof(to_send));
    create_payload(to_send, &response, sizeof(struct response_actions_s));

    sendto(udpfd, to_send, sizeof(to_send), 0, 
					(struct sockaddr*)self->client, sizeof(struct sockaddr_in));

    self->destroy(self);
}


static void destroy_self(struct actions_object_s* self)
{
    free(self);
}

type_object_t *create_action_object(int id)
{
    struct actions_object_s *object = malloc(sizeof(struct actions_object_s));

    object->client_id = id + 1;
    object->handle = &handle_request;
    object->response = &send_response;
    object->destroy = &destroy_self;
    return (type_object_t*)object;
}