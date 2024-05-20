#include "client.h"
#include "../tools.h"
#include <stdlib.h>

void remove_request(struct waiting_request_s **list, struct waiting_request_s *ptr)
{
	sfClock_destroy(ptr->clock);
	pop_address((struct list_s **)list, ptr);
}

int new_request(struct sockaddr *server, int fd, waiting_request_t **request_list, void *information, int type)
{
    request_t *(*functions[])(struct sockaddr*, int, void*) = {
        &create_action_request
    };
    waiting_request_t *new = malloc(sizeof(waiting_request_t));
    new->request = functions[type - 2](server, fd, information);
    new->clock = sfClock_create();
    push_back((struct list_s **)request_list, new);
}