

#ifndef IRESPONSE_H_
#define IRESPONSE_H_

#include "../protocol/types.h"
#ifdef _WIN32
	#include <io.h>
	#include <windows.h>
	#define access _access

    extern HANDLE lock;
#else
    #include <pthread.h>
    extern pthread_mutex_t lock;
#endif


struct IResponse {
    int len;
    int type;
    int request_id;
    Response_body body;
};

#endif /* !IRESPONSE_H_ */
