
#ifndef ACTIONS_H_
#define ACTIONS_H_

#include "types.h"

struct actions_s {
    int len;
    int type;
    Body body;
} request_t;

struct actions_object {
    void (*handle_request)(struct actions_s*);
    void (*send_response)(struct action_object* self);
};

#endif /* !ACTIONS_H_ */
