#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
	#include <io.h>
	// #include <windows.h>
	#include <WS2tcpip.h>
	#define access _access
	
	typedef signed long long int ssize_t;
#else
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <sys/time.h>
#endif

#include <sys/types.h>
#include "server.h"
#include "../tools.h"
#include <SFML/System/Time.h>
#include "../player.h"

#define PORT 5000  // Port for UDP communication
#define MAXLINE 1024


int client_len(struct client **client_list)
{
	int i = 0;

	while (client_list[i])
		i++;
	// printf("je usis la %d\n", i);
	return i;
}

/**
 * resize compress data after remove item
*/
void remove_array_index(void *array, int index, int len)
{
	char **ptr = array;
	int i = 0;

	while (i != index && i < len)
		i++;
	while (i < len) {
		ptr[i] = ptr[i + 1];
		i++;
	}
	ptr[i] = NULL;
}




int is_new_client(struct client *client_list[MAX_CLIENTS], struct sockaddr_in cliaddr)
{
	int i = 0;
	while (client_list[i] && i < MAX_CLIENTS) {
		// printf("stucj la\n");
		if (client_list[i]->socket->sin_addr.s_addr == cliaddr.sin_addr.s_addr && 
			client_list[i]->socket->sin_port == cliaddr.sin_port) {
			return i;
		}
		i++;
	}
	// printf("bien suis que je suis nouveau\n");
	return i;
}

void read_client(int udpfd, fd_set *rset, struct client *client_list[MAX_CLIENTS], int client_count, world_t *map)
{
	struct type_object_s *(*const create_object[])(int, struct client*) = {
		&create_id_object,
		&create_action_object
	};
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
    char buffer[MAXLINE];

	if (FD_ISSET(udpfd, rset)) {
		memset(buffer, 0, MAXLINE);
		ssize_t n = recvfrom(udpfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
		int is_new = is_new_client(client_list, cliaddr);
		// printf("nev 2 id %d\n", is_new);
		if (is_new && client_count >= MAX_CLIENTS) {
			printf("return ? \n");
			return;
		}
		if (client_count < MAX_CLIENTS && client_count == is_new) {
			// printf("passageeeeeeeeeeeeeeeeeeeeeeeeeee %d\n", client_count);
			client_list[client_count++] = new_client(cliaddr, map);

		}
		// printf("number of client %d \n", is_new);
		// write(1, buffer, n);
		if (n >= 0) {
			char digest[MD5_DIGEST_LENGTH] = { 0 };
			// printf("message len %d, size of all %d\n", n, sizeof(struct request_s) + sizeof(digest));

			if (n == sizeof(struct request_s) + sizeof(digest)) {
				cipher(buffer, sizeof(struct request_s), digest);
				if (!memcmp(buffer + sizeof(struct request_s), digest, sizeof(digest))) {
					struct request_s *request = (struct request_s *)buffer;
					// write(1, "message clear\n", strlen("message clear\n"));
					// printf("message type ; %d\n", request->type);
					// printf("new id %d\n", is_new);
					struct type_object_s *request_handler = create_object[request->type - 1](is_new + 1, client_list[is_new]);
					request_handler->handle(request_handler, request, map);
					request_handler->response(request_handler, udpfd);
				}
			}
		}
		if (n < 0) {
			// remove_array_index(client_list, is_new - 1, MAX_CLIENTS);
		}
	}
}

int server_loop(int udpfd, fd_set *rset, server_information_t *server_info, world_t *map) {
	int nready;
    struct timeval timeout;
	int client_count = client_len(server_info->client_list);
	// printf("client count after loop %d \n", client_count);

	FD_ZERO(rset);
	FD_SET(udpfd, rset);

	// Set a timeout to periodically send broadcast messages to clients
	timeout.tv_sec = 0;  // Broadcast every 10 seconds
	timeout.tv_usec = 10000;

	// printf("nev 2 id fffffffffffffffffffffffff\n");

	nready = select(udpfd + 1, rset, NULL, NULL, &timeout);

	// printf("nev 2 id fffffffffffffffffffffffff2222222222\n");
	if (nready > 0) {
		// If the UDP socket is readable, receive the message
		read_client(udpfd, rset, server_info->client_list, client_count, map);
		
	}

	update_players_positions(map);
	
	sfTime time = sfClock_getElapsedTime(server_info->clock);
	if (time.microseconds > 100000) {
		// Broadcast a message to all clients in the list
		// printf("%d\n", client_count);
		// const char* broadcast_message = "Broadcast message from UDP server";
		for (int i = 0; i < client_count; i++) {
			// printf("the list is not empty\n");
			// printf("client id %d\n", client_list[i]->id);
			broadcast(server_info->client_list[i]->socket, server_info->client_list[i]->id, map, udpfd);

			// ssize_t n =  sendto(udpfd, broadcast_message, strlen(broadcast_message), 0, 
			// 		(struct sockaddr*)client_list[i], sizeof(*(client_list[i])));
			// if (n < -1) {
			// 	// printf("peut tre que que deconnecte ?\n");
			// 	remove_array_index(client_list, i, MAX_CLIENTS);
			// 	i--;

			// }
		}
			// printf("\n");
		sfClock_restart(server_info->clock);
	}
}


server_information_t init_server_info(void)
{
	server_information_t server_info;

	memset(&server_info.client_list, 0, sizeof(server_info.client_list));
	server_info.clock = sfClock_create();
	return server_info;
}

int main(int ac, char **av) {
    int udpfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    fd_set rset;
    struct timeval timeout;
    int nready;

    // List of clients for broadcasting
	server_information_t server_info = init_server_info();
    int client_count = 0;

    // Create UDP socket

	#ifdef _WIN32
		WSADATA wsaData;
		if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0){

			printf("Server: WSAStartup failed with error: %ld\n", WSAGetLastError());

			return -1;
		}
		else{
				printf("Server: The Winsock DLL status is: %s.\n", wsaData.szSystemStatus);
		}
		udpfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	#else
		udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	#endif

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	world_t *map = instanciate_file(av[1]);
	
    // Main loop
    while (1) {
		// printf("je suis par la\n");
		server_loop(udpfd, &rset, &server_info, map);
    }

    close(udpfd);
    return 0;
}