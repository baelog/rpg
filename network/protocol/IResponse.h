

#ifndef IRESPONSE_H_
#define IRESPONSE_H_

#include "../protocol/types.h"
#include <pthread.h>

extern pthread_mutex_t lock;

struct IResponse {
    int len;
    int type;
    int request_id;
    Response_body body;
};

#endif /* !IRESPONSE_H_ */
