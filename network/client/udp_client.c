// UDP client program 
// #include <arpa/inet.h> 

#ifdef _WIN32
	#include <io.h>
	// #include <windows.h>
	#include <WS2tcpip.h>
	#include <Windows.h>
	#include <process.h>
	#define access _access
    typedef signed long long int ssize_t;

	HANDLE lock;

#else
	#include <netinet/in.h> 
	#include <pthread.h>
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <sys/time.h>

	pthread_mutex_t lock;
#endif

#include <stdio.h> 
#include <stdlib.h> 
// #include <strings.h> 
// #include <sys/socket.h> 
#include <sys/types.h> 
#include <string.h>
#include "../protocol/id.h"
// #include <arpa/inet.h>
#include <openssl/md5.h>
// #include <unistd.h>
#include <SFML/Graphics/RenderWindow.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
#include "../../include/read.h"
#include "../../include/window.h"
#include "../../include/map.h"
#include "../../include/yaml.h"
// #include "player.h"
#include "../tools.h"
#include "client.h"
// #include <unistd.h>
// #include "types.h"

#define PORT 5000 
#define MAXLINE 1024



#ifdef _WIN32

int sleep(int milliseconds) {
    Sleep(milliseconds*1000);
    return 0;
}
#endif

int get_message(char *buffer, int sockfd, struct sockaddr *servaddr)
{
	int len = sizeof(struct sockaddr_in);
	unsigned char digest[MD5_DIGEST_LENGTH];

	ssize_t n = recvfrom(sockfd, (char*)buffer, MAXLINE, 
					0, servaddr, 
					&len);
	if (n < 0) {
		#ifdef _WIN32
			int errorCode = WSAGetLastError();
    		printf("recvfrom failed with error: %d\n", errorCode);
		#endif

		return 0;
	}
	if (n != sizeof(struct response_id_s) + sizeof(digest)) {
		
		printf("bad message len %lld\n", n, sizeof(struct response_id_s) + sizeof(digest));
		return 0;
	}

	cipher(buffer, sizeof(struct response_id_s), digest);

	if (memcmp(buffer + sizeof(struct response_id_s), digest, sizeof(digest))) {
		printf("message is corrupt\n");
		return 0;
	}
	return 1;
}

int create_socket(struct sockaddr_in *servaddr, char *ip)
{
	int sockfd; 
	#ifdef _WIN32
		WSADATA wsaData;
		if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0){

			printf("Client: WSAStartup failed with error %ld\n", WSAGetLastError());

			// Clean up
			WSACleanup();

			// Exit with error
			return -1;
		}
		else{
			printf("Client: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);
		}
		sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		// setsockopt(sockfd, IPPROTO_UDP, SO_RCVBUF, (char *)&recvBufferSize, sizeof(recvBufferSize));

	#else
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	#endif

	if (sockfd < 0) { 
		return -1;
	}

	memset(servaddr, 0, sizeof(servaddr)); 
	// Filling server information 
	servaddr->sin_family = AF_INET; 
	servaddr->sin_port = htons(PORT); 
	servaddr->sin_addr.s_addr = inet_addr(ip);

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
		printf("je reste stuck ici\n");
	// write(1, "je suis la", strlen("je suis la"));
	} while (sleep(5) || get_message(buffer, sockfd, servaddr) <= 0);

	response = (struct response_id_s*)buffer;
	#ifdef _WIN32
		WaitForSingleObject(lock, INFINITE);
		*id = response->body.id;
		ReleaseMutex(lock);
	#else
		pthread_mutex_lock(&lock);
		*id = response->body.id;
		pthread_mutex_unlock(&lock); 
	#endif
	// printf("my id %d", id);
	return response->body.id;
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
	printf("sockfd1 : %d\n", args->sockfd);
	// #ifdef _WIN32
	// 	WSADATA wsaData;
	// 	if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0){

	// 		printf("Client: WSAStartup failed with error %ld\n", WSAGetLastError());

	// 		// Clean up
	// 		WSACleanup();

	// 		// Exit with error
	// 		return -1;
	// 	}
	// 	else{
	// 		printf("Client thread: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);
	// 	}
	// 	// setsockopt(sockfd, IPPROTO_UDP, SO_RCVBUF, (char *)&recvBufferSize, sizeof(recvBufferSize));

	// #endif

	if (get_id(args->sockfd, (struct sockaddr *)args->servaddr, buffer, sizeof(struct sockaddr_in), &args->client_informations->player_id) < 0)
		return 0;
	
	int is_valide = 0;

	while (args->is_client_alive) {
		
		waiting_answer(buffer, args->sockfd, (struct sockaddr *)args->servaddr, args->client_informations);
	}

	#ifdef _WIN32
		_endthreadex( 0 );
	#endif
	return NULL;
}

void init_client_informations(struct client_information* client_informations)
{
	init_array(client_informations->players, VISION_SIZE);
	init_array(client_informations->scene_object, VISION_SIZE);
	client_informations->player_id = 0;
	client_informations->requests = NULL;
}

int main(int ac, char **av) 
{
	#ifdef _WIN32
		HANDLE  hThread;
		unsigned threadID;
	#else
		pthread_t tid;
	#endif

	struct sockaddr_in servaddr;
	struct client_information client_informations;
	char buffer[MAXLINE];

	int sockfd = create_socket(&servaddr, av[1]);
	if (sockfd < 0) {
		printf("je suis la\n");
		return 0;
	}
	
	init_client_informations(&client_informations);
	#ifdef _WIN32
		lock = CreateMutex(NULL, FALSE, NULL);
	#else
		pthread_mutex_init(&lock, NULL);
	#endif

	struct thread_args args = {&client_informations, sockfd, (void*)&servaddr, 1};
	// pthread_create(&tid, NULL, handle_server_connection, (void *)&args); 

	#ifdef _WIN32
		// hThread = (HANDLE)_beginthread(handle_server_connection, 0, (void *)&args);
		printf("sockfd0 : %d\n", args.sockfd);
		hThread = (HANDLE)_beginthreadex(NULL, 0, &handle_server_connection, &args, 0, &threadID);
	#else
		pthread_create(&tid, NULL, handle_server_connection, (void *)&args); 
	#endif
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
			static int moving = 0;
			int prev = moving;
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
			if (event.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyUp) && !(moving & UP))
				moving ^= UP;
			if (event.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyRight) && !(moving & RIGHT))
				moving ^= RIGHT;
			if (event.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyDown) && !(moving & DOWN))
				moving ^= DOWN;
			if (event.type == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyLeft) && !(moving & LEFT))
				moving ^= LEFT;
			if (event.type == sfEvtKeyReleased && !sfKeyboard_isKeyPressed(sfKeyUp) && (moving & UP))
				moving ^= UP;
			if (event.type == sfEvtKeyReleased && !sfKeyboard_isKeyPressed(sfKeyRight) && (moving & RIGHT))
				moving ^= RIGHT;
			if (event.type == sfEvtKeyReleased && !sfKeyboard_isKeyPressed(sfKeyDown) && (moving & DOWN))
				moving ^= DOWN;
			if (event.type == sfEvtKeyReleased && !sfKeyboard_isKeyPressed(sfKeyLeft) && (moving & LEFT))
				moving ^= LEFT;
			if (moving != prev) {
				printf("moving %d\n", moving);
				new_request((struct sockaddr *)&servaddr, sockfd, &client_informations.requests, (void*)&moving, ACTIONS);
				// printf("the fuck i'am here\n");
			}
        }
			// printf("je rentre enfin%d\n", client_informations.player_id);

		if (client_informations.player_id) {
			// printf("je rentre enfin\n");
			// if (get_message(buffer, sockfd, (struct sockaddr *)&servaddr)) {
			// 	create_tiles(client_informations->scene_object, (struct response_id_s *)buffer);
			// }
			for (int i = 0; client_informations.scene_object[i] && i < VISION_SIZE; i++)
				client_informations.scene_object[i]->print(client_informations.scene_object[i], window);
			for (int i = 0; client_informations.players[i] && i < MAX_PLAYER; i++)
				client_informations.players[i]->print(client_informations.players[i], window);
			/* Clear the screen */
			/* Update the window */
			sfRenderWindow_display(window);
			sfRenderWindow_clear(window, sfBlack);
		}
    }
	args.is_client_alive = 0;
    /* Cleanup resources */
    sfRenderWindow_destroy(window);
	#ifdef _WIN32
		WaitForSingleObject( hThread, INFINITE );
		CloseHandle( hThread );
	#else
		pthread_join(tid, NULL);
	#endif
	// pthread_exit(NULL);
	close(sockfd);
	return 0; 
} 
