#include "id.h"
#include <stdlib.h>

int new_id(void)
{
    static int id = 0;
    
    id += 1;
    return id;
}

static void handle_request(struct id_s)
{

}

static void send_response(struct id_object* self)
{

}

type_object_t *create_id_object(void)
{
    struct id_object_s *object = malloc(sizeof(struct id_object_s));

    object->handle_request = &handle_request;
    object->send_response = &send_response;
    return (type_object_t*)object;
}