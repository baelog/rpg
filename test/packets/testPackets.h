#ifndef PACKET_TEST
#define PACKET_TEST

#define MAX_PCKT 10

void test_PacketsAdd(void);
void test_SequencesCreate(void);

int countPacket(struct packetList *packets);
int allSamePacketInSequences(struct sequences *sq);
int countSquences(struct sequences *sq);


#endif