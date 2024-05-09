/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

// #include "protocol/types.h"
#include <SFML/System/Vector2.h>
#include <openssl/md5.h>

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

struct type_object_s {
    void (*handle_request)(struct request_s*);
    void (*send_response)(struct type_object* self);
};

int cipher(void *data, size_t size, __u_char digest[MD5_DIGEST_LENGTH]);

#endif /* !SERVER_H_ */
