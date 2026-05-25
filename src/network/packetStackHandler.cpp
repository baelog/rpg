#include "packet.h"
#include <cstdint>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void sendMessage(char *payload, int size, int sockfd, struct sockaddr *servaddr, int servaddr_size)
{
    static int sequenceID = 0;

    struct packet p;

    int packetID = 0;
    int maxPacket = size / PAYLOAD_SIZE + (size % PAYLOAD_SIZE ? 1 : 0);

    while (size > 0) {
        memset(&p, 0, sizeof(p));
        p.size = sizeof(p);
        p.sequenceID = sequenceID;
        p.packetID = packetID;
        p.packetNb = maxPacket;
        memcpy(p.payload, payload + PAYLOAD_SIZE * packetID, PAYLOAD_SIZE);
        cipher(&p, (char*)&p.size - (char*)&p.MD5, p.MD5);
        size -= PAYLOAD_SIZE;

        sendto(sockfd, (const char*)&p, sizeof(p), 
                0, servaddr, servaddr_size);
        
        packetID++;
    }

    sequenceID = sequenceID + 1 % MAX_SEQUENCE_ID;

}

void printMemory(char *ptr, size_t size) {
	printf("memory start : ");
	size_t i = 0;
	for (; i < size; i++) {
		printf("%X ", ptr[i]);
	}
	printf("\n");
	printf("%ld\n", i);
}

struct packetList *createPacket(struct packetList *packets, struct packet *pckt)
{
	struct packetList *newNode = (struct packetList*)malloc(sizeof(struct packetList));
	// printf("je tourne la\n");
	if (!newNode)
		return NULL;
	memset(newNode, 0, sizeof(*newNode));

	newNode->packet = (struct packet*)malloc(sizeof(struct packet));
	newNode->next = packets;
	if (!newNode->packet)
		return NULL;

	// printMemory((char*)pckt, sizeof(struct packet));
	memcpy(newNode->packet, pckt, sizeof(struct packet));
	
	// printf(" next after creation%p\n",  newNode->next);
	return newNode;
}

int insertPacket(struct packetList **packets, struct packet *pckt)
{
	struct packetList *ac = *packets;
	struct packetList *prev = *packets;
	
	
	if (!ac) {
		*packets = createPacket(ac, pckt);
		ac = *packets;
		return 0;
	}
	
	// printf("je passe ici a un moment\n");
	while (ac && ac->packet->packetID != pckt->packetID && ac->packet->packetID < pckt->packetID) {
		// printf("insert: %d\n", ac->packet->packetID);
		prev = ac;
		ac = ac->next;
	}
	// printf("\n");

	//maybe insert it oon the middle
	// printf("je sort\n %p", packet);
	if (ac && ac->packet->packetID == pckt->packetID)
		return 0;

	struct packetList *newNode = createPacket(ac, pckt);

	if (prev == ac)
		*packets = newNode;
	else
		prev->next = newNode;

	return 0;
}

struct sequences *createSequences(struct sequences **sq, struct packet *pckt)
{
	struct sequences *newSequences = (struct sequences*)malloc(sizeof(struct sequences));
	if (!newSequences)
		return NULL;
	
	// printf("pckt->sequenceID : %d\n", pckt->sequenceID);
	newSequences->packetNumber = pckt->packetNb;
	newSequences->sequenceID = pckt->sequenceID;
	newSequences->packets = NULL;
	newSequences->next = NULL;
	
	if (!*sq) {
		*sq = newSequences;
		return newSequences;
	}

	struct sequences *act = (*sq)->next;
	struct sequences *prev = *sq;

	if (prev->packetNumber > pckt->sequenceID) {
		newSequences->next = prev;
		*sq = newSequences;
		return newSequences;
	}

	while(act && act->packetNumber > pckt->sequenceID) {
		prev = act;
		act = act->next;
	}

	prev->next = newSequences;
	newSequences->next = act;
	return newSequences;
}

int addToPlace(struct sequences **sq, struct packet *pckt) 
{
	struct sequences *act = *sq;
	struct sequences *prev = *sq;
	
	struct packetList *packets;
	if (!*sq) {
		createSequences(sq, pckt);
		act = *sq;
		if (!act) {
			return 0;
		}
	}

	while (act && act->sequenceID != pckt->sequenceID) {
		prev = act;
		act = act->next;
		// printf("loop\n");
	}
	//todo maybe insert it oon the middle
	if (!act)
		act = createSequences(sq, pckt);

	insertPacket(&act->packets, pckt);
	return 0;
}

int clearPackets(struct packetList **packets) {
	struct packetList *pckt = *packets;

	while (*packets) {
		pckt = *packets;
		*packets = pckt->next;
		free(pckt->packet);
		free(pckt);
	}
	*packets = NULL;

	return 0;
}

int clearSquences(struct sequences **sq)
{
	struct sequences *tmp = *sq;


	while (*sq) {
		tmp = *sq;
		*sq = tmp->next;
		clearPackets(&tmp->packets);
		free(tmp);
	}
	*sq = NULL;

	return 0;
}

int receiveMessage(char *buffer, int sockfd, struct sockaddr *servaddr)
{
    int len = sizeof(struct sockaddr_in);
    int messageLen = sizeof(struct packet);
	// unsigned char digest[MD5_DIGEST_LEN];

	ssize_t n = recvfrom(sockfd, (char*)buffer, messageLen, 
					0, servaddr, 
					(socklen_t *)&len);
	if (n < 0) {
		#ifdef _WIN32
			int errorCode = WSAGetLastError();
    		printf("recvfrom failed with error: %d\n", errorCode);
		#endif

		return 0;
	}
	if (n != sizeof(struct packet)) {
		
		printf("bad message len %ld\n, %ld\n", n, sizeof(struct packet));
		return 0;
	}

	struct packet *msg = (struct packet*)buffer;
	__u_char digest[MD5_DIGEST_LEN] = {0};

	cipher(msg, (char*)&(msg->size) - (char*)&(msg->MD5), digest);

	if (memcmp(msg->MD5, digest, MD5_DIGEST_LEN)) {
		printf("message is corrupt\n");
		return 0;
	}
	return 1;
}