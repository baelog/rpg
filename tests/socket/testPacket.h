#ifndef TEST_PACKET
#define TEST_PACKET

#include "../../src/network/packet.h"

#define MAX_PCKT 10

int countPacket(struct packetList *packets);
int countSquences(struct sequences *sq);
int allSamePacketInSequences(struct sequences *sq);
int arePacketInOrder(struct packetList *packets);


#endif