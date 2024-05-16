
#ifndef CLIENT_H_
#define CLIENT_H_

typedef struct response_s response_t; 

#define VISION_SIZE 30

typedef struct waiting_request_s {
    response_t *request;
    struct waiting_request_s *next;
}waiting_request_t;


typedef struct tiles_s tiles_t;
typedef struct player_s player_t;

struct client_information {
    tiles_t *scene_object[VISION_SIZE];
    player_t *players[VISION_SIZE];
    waiting_request_t *requests;
    int player_id;
};

struct thread_args {
    struct client_information* client_informations;
    int sockfd;
    struct sockaddr_in *servaddr;
};
#endif /* !CLIENT_H_ */
