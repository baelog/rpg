#ifndef PACKET_MASSAGE
#define PACKET_MASSAGE

#include "packetHandler.h"
#define MAX_SEQUENCE_ID 2048

#define PAYLOAD_SIZE 256

#ifndef MD5_DIGEST_LEN
#define MD5_DIGEST_LEN 16
#endif

struct packet {
    int size;
    /**
     * client request - mach the client request id to avoid deletion if the
     * message need a resend
     * int clientRequestID
     * */
    int sequenceID;
    int packetNb;
    int packetID;
    char payload[PAYLOAD_SIZE];
    __u_char MD5[MD5_DIGEST_LEN];
};

struct packetList {
    struct packet *packet;
    struct packetList *next;
};

struct sequences {
    int playerID;
    int sequenceID;
    int packetNumber;
    struct packetList *packets;
    struct sequences *next;
};

struct packetList *createPacket(struct packetList *packets, struct packet *pckt);
int insertPacket(struct packetList **packets, struct packet *pckt);
struct sequences *createSequences(struct sequences **sq, struct packet *pckt);
int addToPlace(struct sequences **sq, struct packet *pckt);
int clearPackets(struct packetList **packets);
int clearSquences(struct sequences **sq);

//todo clear a spsecifique sequece


void printMemory(char *ptr, size_t size);

#endif