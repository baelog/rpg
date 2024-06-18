#include "server/server.h"

struct sockaddr *get_client_socket(struct client *cli)
{
    return (struct sockaddr *)cli->socket;
}

int get_client_id(struct client *cli)
{
    return cli->id;
}

int get_client_state(struct client *cli)
{
    return cli->state;
}