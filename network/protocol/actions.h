
#ifndef ACTIONS_H_
#define ACTIONS_H_

#include "types.h"

struct response_actions_s {
    int len;
    int type;
    Request_body body;
};

struct request_actions_s {
    int len;
    int type;
    Request_body body;
};

struct actions_object {
    void (*handle_request)(struct request_actions_s*);
    void (*send_response)(struct action_object* self);
};

#endif /* !ACTIONS_H_ */
