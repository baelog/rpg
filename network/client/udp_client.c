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

// #include "types.h"

#define PORT 5000 
#define MAXLINE 1024

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

int get_id(int sockfd, struct sockaddr *servaddr, char *buffer, int servaddr_size) {
	struct request_id_s request;
	memset(&request, 0, sizeof(struct request_id_s));
	request.len = sizeof(struct request_id_s);
	request.type = ID;
	request.body.value = 0;

	char to_send[sizeof(request) + MD5_DIGEST_LENGTH];

	create_payload(to_send, &request, sizeof(request));

	sendto(sockfd, (const char*)to_send, sizeof(to_send), 
		0, servaddr, servaddr_size);
	write(1, "je suis la", strlen("je suis la"));
	if (!get_message(buffer, sockfd, &servaddr))
		return -1;

	return 0;
}

void create_tiles(tiles_t **array, struct response_id_s *response)
{
	tiles_t *(*backgroundConstructor[]) (sfVector2f) = {
		&create_ground, //TODO create the void finction
		&create_wall,
		&create_ground
	};
	int j = 0;
	for (int i = 0; i != VISION_SIZE && response->body.object[i].type >= 0; i++) {
		
		// if (!response->body.object[i].type)
		// 	printf("player: %d %f %f\n", response->body.object[i].player_type, response->body.object[i].position.x, response->body.object[i].position.y);
		if (response->body.object[i].type)
			array[j++] = backgroundConstructor[response->body.object[i].type](response->body.object[i].position);
	}
	while (j < VISION_SIZE)
		array[j++] = NULL;
}

int main() 
{ 
	char buffer[MAXLINE];
	struct sockaddr_in servaddr; 
	int sockfd = create_socket(&servaddr); 
 
	if (sockfd < 0)
		return 0;

	if (get_id(sockfd, &servaddr, buffer, sizeof(servaddr)) < 0)
		return 0;
	struct response_id_s *response = (struct response_id_s*)buffer;
	
	
    sfVideoMode mode = {WIDTH, HEIGHT, BITSPERPIXEL};
    sfRenderWindow* window;
    sfEvent event;
    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    /* Load a sprite to display */
    tiles_t *scene_object[VISION_SIZE] = { NULL };
    
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
		if (get_message(buffer, sockfd, &servaddr)) {
			create_tiles(scene_object, (struct response_id_s *)buffer);
		}
		for (int i = 0; scene_object[i] && i < VISION_SIZE; i++)
			scene_object[i]->print(scene_object[i], window);
        /* Clear the screen */
        /* Update the window */
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
    }
    /* Cleanup resources */
    sfRenderWindow_destroy(window);
	close(sockfd); 
	return 0; 
} 
