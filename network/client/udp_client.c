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

// #include "types.h"

#define PORT 5000 
#define MAXLINE 1024 

int main() 
{ 
	int sockfd; 
	char buffer[MAXLINE]; 
	char* message = "Hello Server"; 
	struct sockaddr_in servaddr; 

	int n, len; 
	// Creating socket file descriptor 
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
		printf("socket creation failed"); 
		exit(0); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	// send hello message to server 

	u_char digest[MD5_DIGEST_LENGTH];
	struct request_id_s request;
	memset(&request, 0, sizeof(struct request_id_s));
	request.len = sizeof(struct request_id_s);
	request.type = ID;
	request.body.value = 32;

	// request.len = htons(request.len);
	// request.type = htons(request.type);
	// request.body.value = htons(request.body.value);

	// printf("%d %d %d\n", request.len, request.type, request.body.value);
	cipher(&request, sizeof(struct request_id_s), digest);
	
	char to_send[sizeof(request) + sizeof(digest)] = {0};
	
	memcpy(to_send, (char*)&request, sizeof(request));
	memcpy(to_send + sizeof(request), digest, sizeof(digest));

	// write(1, request, sizeof(request));

	// write(1, to_send, sizeof(to_send));

	sendto(sockfd, (const char*)to_send, sizeof(to_send), 
		0, (const struct sockaddr*)&servaddr, 
		sizeof(servaddr));
	
	n = recvfrom(sockfd, (char*)buffer, MAXLINE, 
					0, (struct sockaddr*)&servaddr, 
					&len);
	// write(1, buffer + sizeof(struct response_id_s), sizeof(digest));
	write(1, buffer , n);
	
	// printf("%d %d\n", n, sizeof(struct response_id_s));
	if (n != sizeof(struct response_id_s) + sizeof(digest)) {
		printf("bad message len\n");
		return 0;
	}

	memset(digest, 0, sizeof(digest));

	write(1, buffer , sizeof(struct response_id_s));

	cipher(buffer, 16, digest);
	
	write(1, digest, sizeof(digest));

	// printf("%d \n", sizeof(struct response_id_s))
	if (memcmp(buffer + 16, digest, sizeof(digest))) {
		printf("message is corrupt\n");
		return 0;
	}

	struct response_id_s *response = (struct response_id_s*)buffer;
	printf("%d %d %d\n", response->type, response->len, response->body.id);
	// sendto(sockfd, (const char*)digest, MD5_DIGEST_LENGTH, 
	// 	0, (const struct sockaddr*)&servaddr, 
	// 	sizeof(servaddr));
	// receive server's response 
	// printf("Message from server: "); 

	
	// while (1) {
	// 	n = recvfrom(sockfd, (char*)buffer, MAXLINE, 
	// 				0, (struct sockaddr*)&servaddr, 
	// 				&len); 
	// 	if (n < 0)
	// 		exit(0);
	// 	buffer[n] = '\0';
	// 	puts(buffer); 
	// }
	close(sockfd); 
	return 0; 
} 
