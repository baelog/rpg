#include "message.h"
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
        cipher(&p, (void*)&p.size - (void*)&p.MD5, p.MD5);
        size -= PAYLOAD_SIZE;

        sendto(sockfd, (const char*)&p, sizeof(p), 
                0, servaddr, servaddr_size);
        
        packetID++;
    }

    sequenceID = sequenceID + 1 % MAX_SEQUENCE_ID;

}

struct packetList *createPacket(struct packetList **packets, struct packet *pckt)
{
	struct packetList *new = malloc(sizeof(struct packetList));

	if (!new)
		return NULL;

	new->packet = malloc(sizeof(struct packet));
	if (!new->packet)
		return NULL;

	memcpy(new->packet, pckt, sizeof(struct packet));
	
	return new;
}

int insertPacket(struct packetList **packets, struct packet *pckt)
{
	struct packetList *ac = *packets;
	struct packetList *prev = *packets;
	
	
	if (!ac) {
		*packets = createPacket(packets, pckt);
		ac = *packets;
	}
	
	// printf("je passe ici a un moment\n");
	while (ac && ac->packet->packetID != pckt->packetID) {
		// printf("insert: %d\n", ac->packet->packetID);
		prev = ac;
		ac = ac->next;
	}
	// printf("\n");

	//maybe insert it oon the middle
	if (!ac)
		prev->next = createPacket(packets, pckt);
	return 0;
}

struct sequences *createSequences(struct sequences **sq, struct packet *pckt)
{
	struct sequences *new = malloc(sizeof(struct sequences));
	if (!new)
		return NULL;
	
	// printf("pckt->sequenceID : %d\n", pckt->sequenceID);
	new->packetNumber = pckt->packetNb;
	new->sequenceID = pckt->sequenceID;
	new->packets = NULL;
	new->next = NULL;
	
	if (!*sq) {
		*sq = new;
		return new;
	}

	struct sequences *act = (*sq)->next;
	struct sequences *prev = *sq;

	if (prev->packetNumber > pckt->sequenceID) {
		new->next = prev;
		*sq = new;
		return new;
	}

	while(act && act->packetNumber > pckt->sequenceID) {
		prev = act;
		act = act->next;
	}

	prev->next = new;
	new->next = act;
	return new;
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
			// printf("pas de création\n");
			return 0;
		}
	}

	// printf("sequence id :%d\n", act->sequenceID);
	while (act && act->sequenceID != pckt->sequenceID) {
		prev = act;
		act = act->next;
		// printf("loop\n");
	}
	//maybe insert it oon the middle
	if (!act)
		act = createSequences(sq, pckt);

	insertPacket(&act->packets, pckt);
	return 0;
}

int receiveMessage(char *buffer, int sockfd, struct sockaddr *servaddr)
{
    int len = sizeof(struct sockaddr_in);
    int messageLen = sizeof(struct packet);
	// unsigned char digest[MD5_DIGEST_LEN];

	ssize_t n = recvfrom(sockfd, (char*)buffer, messageLen, 
					0, servaddr, 
					&len);
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
	char digest[MD5_DIGEST_LEN] = {0};

	cipher(msg, (void*)&msg->size - (void*)&msg->MD5, digest);

	if (memcmp(msg->MD5, digest, MD5_DIGEST_LEN)) {
		printf("message is corrupt\n");
		return 0;
	}
	return 1;
}