
#ifndef ID_H_
#define ID_H_

#include "types.h"

struct id_s {
    int len;
    int type;
    Body body;
};


struct id_object_s {
    void (*handle_request)(struct id_s*);
    void (*send_response)(struct id_object_s* self);
};


#endif /* !ID_H_ */
