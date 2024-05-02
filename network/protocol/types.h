#ifndef NETWORK_TYPES_H_
#define NETWORK_TYPES_H_

#include <SFML/System/Vector2.h>

typedef struct request_s request_t;
typedef struct type_object_s type_object_t;

typedef union {
    int value; // error for now maybe usefull later
    sfVector2f vector;
}Request_body;

typedef union {
    int id;
    sfVector2f position;
}Response_ID;


#endif /* !TYPES_H_ */
