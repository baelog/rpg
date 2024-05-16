// UDP client program 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <string.h>
#include "../protocol/id.h"
#include <arpa/inet.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <SFML/Graphics/RenderWindow.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/read.h"
#include "../../include/window.h"
#include "../../include/map.h"
#include "../../include/yaml.h"
#include <pthread.h>
// #include "player.h"
#include "../tools.h"
#include "client.h"

// #include "types.h"

#define PORT 5000 
#define MAXLINE 1024

pthread_mutex_t lock;

int get_message(char *buffer, int sockfd, struct sockaddr *servaddr)
{
	int len;
	u_char digest[MD5_DIGEST_LENGTH];

	ssize_t n = recvfrom(sockfd, (char*)buffer, MAXLINE, 
					0, servaddr, 
					&len);

	if (n != sizeof(struct response_id_s) + sizeof(digest)) {
		printf("bad message len\n");
		return 0;
	}

	cipher(buffer, sizeof(struct response_id_s), digest);

	if (memcmp(buffer + sizeof(struct response_id_s), digest, sizeof(digest))) {
		printf("message is corrupt\n");
		return 0;
	}
	return 1;
}

int create_socket(struct sockaddr_in *servaddr)
{
	int sockfd; 

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
		return -1;
	}

	memset(servaddr, 0, sizeof(servaddr)); 
	// Filling server information 
	servaddr->sin_family = AF_INET; 
	servaddr->sin_port = htons(PORT); 
	servaddr->sin_addr.s_addr = inet_addr("127.0.0.1");

	return sockfd;

}

int get_id(int sockfd, struct sockaddr *servaddr, char *buffer, int servaddr_size, int *id) {
	struct request_id_s request;
	struct response_id_s *response;

	memset(&request, 0, sizeof(struct request_id_s));
	request.len = sizeof(struct request_id_s);
	request.type = ID;
	request.body.value = 0;

	char to_send[sizeof(request) + MD5_DIGEST_LENGTH];

	create_payload(to_send, &request, sizeof(request));

	do {
	sendto(sockfd, (const char*)to_send, sizeof(to_send), 
		0, servaddr, servaddr_size);
	// write(1, "je suis la", strlen("je suis la"));
	} while (!sleep(5) && !get_message(buffer, sockfd, servaddr));

	response = (struct response_id_s*)buffer;
	pthread_mutex_lock(&lock);
	*id = response->body.id;
	pthread_mutex_unlock(&lock); 
	// printf("my id %d", id);
	return response->body.id;
}

void create_tiles(tiles_t **array, struct response_id_s *response)
{
	tiles_t *(*backgroundConstructor[]) (sfVector2f) = {
		&create_ground, //TODO create the void finction
		&create_wall,
		&create_ground
	};
	int j = 0;
	pthread_mutex_lock(&lock);

	for (int i = 0; i != VISION_SIZE && response->body.object[i].type >= 0; i++) {
		
		// if (!response->body.object[i].type)
		// 	printf("player: %d %f %f\n", response->body.object[i].player_type, response->body.object[i].position.x, response->body.object[i].position.y);
		if (response->body.object[i].type) {
			// printf("not my type ? %d\n", response->body.object[i].type);
			array[j++] = backgroundConstructor[response->body.object[i].type](response->body.object[i].position);
		}
	}
	pthread_mutex_unlock(&lock);
	while (j < VISION_SIZE)
		array[j++] = NULL;
}

/**
 * this function is to get message from server
 * @param pointer take a pointer of struct to get args
 * @return nothing
*/
void *handle_server_connection(void *ptr)
{
	struct thread_args *args = ptr;
	char buffer[MAXLINE];

	if (get_id(args->sockfd, (struct sockaddr *)args->servaddr, buffer, sizeof(struct sockaddr_in), &args->client_informations->player_id) < 0)
		return 0;
	
	if (get_message(buffer, args->sockfd, (struct sockaddr *)args->servaddr)) {
		create_tiles(args->client_informations->scene_object, (struct response_id_s *)buffer);
	}
}

void init_client_informations(struct client_information* client_informations)
{
	init_array(client_informations->players, VISION_SIZE);
	init_array(client_informations->scene_object, VISION_SIZE);
	client_informations->player_id = 0;
	client_informations->requests = NULL;
}

int main(void) 
{ 
	pthread_t tid;
	struct sockaddr_in servaddr;
	struct client_information client_informations;
	char buffer[MAXLINE];

	int sockfd = create_socket(&servaddr); 
	if (sockfd < 0)
		return 0;
	
	init_client_informations(&client_informations);

	struct thread_args args = {&client_informations, sockfd, (void*)&servaddr};
	pthread_create(&tid, NULL, handle_server_connection, (void *)&args); 
	// if (get_id(sockfd, (struct sockaddr *)&servaddr, buffer, sizeof(servaddr)) < 0)
	// 	return 0;
	// struct response_id_s *response = (struct response_id_s*)buffer;
	
	
    sfVideoMode mode = {WIDTH, HEIGHT, BITSPERPIXEL};
    sfRenderWindow* window;
    sfEvent event;
    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    /* Load a sprite to display */
    // tiles_t *scene_object[VISION_SIZE] = { NULL };
    // player_t *players[VISION_SIZE] = { NULL };
    
    sfRenderWindow_setFramerateLimit(window, FRAMERATELIMIT);

    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
			// printf("je rentre enfin%d\n", client_informations.player_id);

		if (client_informations.player_id) {
			// printf("je rentre enfin\n");
			// if (get_message(buffer, sockfd, (struct sockaddr *)&servaddr)) {
			// 	create_tiles(client_informations->scene_object, (struct response_id_s *)buffer);
			// }
			for (int i = 0; client_informations.scene_object[i] && i < VISION_SIZE; i++)
				client_informations.scene_object[i]->print(client_informations.scene_object[i], window);
			/* Clear the screen */
			/* Update the window */
			sfRenderWindow_display(window);
			sfRenderWindow_clear(window, sfBlack);
		}
    }
    /* Cleanup resources */
    sfRenderWindow_destroy(window);
	pthread_join(tid, NULL);
	close(sockfd); 
	return 0; 
} 
