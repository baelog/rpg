#ifndef NETWORK_TYPES_H_
#define NETWORK_TYPES_H_

// #include <SFML/System/Vector2.hpp>

typedef struct request_s request_t;
typedef struct type_object_s type_object_t;
typedef struct world_s world_t;
typedef struct player_s player_t;
typedef struct IResponse IResponse;
typedef struct client client_t;
typedef struct sockaddr_in sockaddr_in;

#define VISION_SIZE 30

struct PointF_s {
    double x;
    double y;
};

struct vision_s {
    PointF_s position;
    int type;
    int player_type;
};

typedef union {
    int value;
    PointF_s vector;
}Request_body;

typedef union {
    int id;
    struct vision_s object[VISION_SIZE];
}Response_body;

enum type {
    BROADDCAST,
    ID,
    ACTIONS,
    INVENTARY,
    _ERROR
};

#endif /* !TYPES_H_ */