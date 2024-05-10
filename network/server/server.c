#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "server.h"

#define PORT 5000  // Port for UDP communication
#define MAXLINE 1024
#define MAX_CLIENTS 10

static int array_len(void *array)
{
	char **ptr = array;
	int i = 0;

	while (ptr[i])
		i++;
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


struct client *new_client(struct sockaddr_in client)
{
	static int client_id = 0;

	struct client *new_client = malloc(sizeof(struct client));
	struct sockaddr_in *new = malloc(sizeof(struct sockaddr_in));

	memcpy(new, &client, sizeof(client));
	new_client->socket = new;
	new_client->id = client_id++;

	return new_client;
}

int is_new_client(struct client *client_list[MAX_CLIENTS], struct sockaddr_in cliaddr)
{
	int i = 0;
	for (;client_list[i]; i++) {
		if (client_list[i]->socket->sin_addr.s_addr == cliaddr.sin_addr.s_addr && 
			client_list[i]->socket->sin_port == cliaddr.sin_port) {
			return i;
		}
	}
	return 0;
}

void read_client(int udpfd, fd_set *rset, struct client *client_list[MAX_CLIENTS], int client_count)
{
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
    char buffer[MAXLINE];

	if (FD_ISSET(udpfd, rset)) {
		memset(buffer, 0, MAXLINE);
		ssize_t n = recvfrom(udpfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
		int is_new = is_new_client(client_list, cliaddr);
		if (!is_new && client_count >= MAX_CLIENTS)
			return;
		if (!is_new && client_count < MAX_CLIENTS) {
			client_list[client_count++] = new_client(cliaddr);
		}
		write(1, buffer, n);
		if (n >= 0) {
			char digest[MD5_DIGEST_LENGTH] = { 0 };
			// printf("message len %d, size of all %d\n", n, sizeof(struct request_s) + sizeof(digest));

			if (n == sizeof(struct request_s) + sizeof(digest)) {
				cipher(buffer, sizeof(struct request_s), digest);
				if (!memcmp(buffer + sizeof(struct request_s), digest, sizeof(digest))) {
					struct request_s *request = buffer;
					// write(1, "message clear\n", strlen("message clear\n"));
					printf("message type ; %d\n", request->type);
					struct type_object_s *request_handler = create_object[request->type](is_new);
					request_handler->handle(request_handler, request, (struct sockaddr_in*)&cliaddr);
					request_handler->response(request_handler, udpfd);
				}
			}
		}
		if (n < 0) {
			remove_array_index(client_list, is_new, MAX_CLIENTS);
			printf("je suis la pour delete les clients mais en backup\n");
		}
	}
}

int server_loop(int udpfd, fd_set *rset, struct client *client_list[MAX_CLIENTS]) {
	int nready;
    struct timeval timeout;
	int client_count = array_len((client_list));

	FD_ZERO(rset);
	FD_SET(udpfd, rset);

	// Set a timeout to periodically send broadcast messages to clients
	timeout.tv_sec = 0;  // Broadcast every 10 seconds
	timeout.tv_usec = 1000000;

	nready = select(udpfd + 1, rset, NULL, NULL, &timeout);

	if (nready > 0) {
		// If the UDP socket is readable, receive the message
		read_client(udpfd, rset, client_list, client_count);
		
	} else {
		// Broadcast a message to all clients in the list
		printf("%d\n", client_count);
		const char* broadcast_message = "Broadcast message from UDP server";
		for (int i = 0; i < client_count; i++) {
			ssize_t n =  sendto(udpfd, broadcast_message, strlen(broadcast_message), 0, 
					(struct sockaddr*)client_list[i], sizeof(*(client_list[i])));
			if (n < -1) {
				printf("peut tre que que deconnecte ?\n");
				remove_array_index(client_list, i, MAX_CLIENTS);
				i--;

			}
		}
	}
}

int main() {
    int udpfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    fd_set rset;
    struct timeval timeout;
    int nready;

    // List of clients for broadcasting
    struct client *client_list[MAX_CLIENTS + 1] = { NULL };
    int client_count = 0;

    // Create UDP socket
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Main loop
    while (1) {
		server_loop(udpfd, &rset, client_list);
    }

    close(udpfd);
    return 0;
}