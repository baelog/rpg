#include "id.h"
#include <stdlib.h>
#include <string.h>

int new_id(void)
{
    static int id = 0;
    
    id += 1;
    return id;
}

static void handle_request(struct request_id_s* request, size_t request_len)
{
    __u_char md5[MD5_DIGEST_LENGTH];
    char *ptr = request;
    char *md;

    if (request_len != sizeof(struct request_id_s) + MD5_DIGEST_LENGTH)
        return;
    md = ptr + sizeof(struct request_id_s);
    cipher(request, request_len, md5);
    if (strncmp(md, md5, MD5_DIGEST_LENGTH))
        return;
    printf("le message a l'aire bien recu\n");
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