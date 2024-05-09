
#ifndef ID_H_
#define ID_H_

#include "types.h"
#include <openssl/md5.h>

int cipher(void *data, size_t size, __u_char digest[MD5_DIGEST_LENGTH]);

struct response_id_s {
    int len;
    int type;
    Response_body body;
};

struct request_id_s {
    int len;
    int type;
    Request_body body;
};

struct id_object_s {
    void (*handle_request)(struct request_id_s*);
    void (*send_response)(struct id_object_s* self);
};

#endif /* !ID_H_ */
