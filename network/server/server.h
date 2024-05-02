/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include "protocol/types.h"

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
    int value;
};

struct response_s {
    int len;
    int type;
    Body body;
};

struct type_object_s {
    void (*handle_request)(request_t*);
    void (*send_response)(struct type_object* self);
};

#endif /* !SERVER_H_ */
