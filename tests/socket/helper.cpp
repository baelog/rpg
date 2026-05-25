#include "../../src/network/packet.h"
#include <stdio.h>

int countPacket(struct packetList *packets) {
	int i = 0;

    // printf("%p\n", packets);
	while (packets) {
        // printf("%i\n", packets->packet->packetID);
		packets = packets->next;
		i++;
	}
    // printf("value %d \n", i);
	return i;
}

int countSquences(struct sequences *sq) {
	int i = 0;

	while (sq) {
		sq = sq->next;
		i++;
	}
	return i;
}

int arePacketInOrder(struct packetList *packets) {
    int packetID = 0;
    while (packets) {
        if (packets->packet->packetID < packetID)
            return 1;
        packetID = packets->packet->packetID;
        packets = packets->next;
    }
    return 0;
}


int allSamePacketInSequences(struct sequences *sq) {
	int i = 0;
    int count = 0;
    int tmp = 0;

	while (sq) {
        if (!sq->packets)
            printf("nothing to count\n");
        tmp = countPacket(sq->packets);
        if (i && count != tmp)
            return 0;
        count = tmp;
		i++;
		sq = sq->next;
        printf("count: %d, tmp: %d\n", count, tmp);
	}
	return count;
}