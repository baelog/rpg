#include "server.hpp"

int Client::genereteID()
{
    IDGenerated++;
    return IDGenerated;
}


Client::Cient(struct sockaddr_in *socket) : _socket(socket)
{
    _id = genereteID();
}

Client::~Cient(struct sockaddr_in *socket)
{
}