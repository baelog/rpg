#include "../../network/protocol/message.h"
#include <stdio.h>

int countPacket(struct packetList *packets) {
	int i = 0;

	while (packets) {
		packets = packets->next;
		i++;
	}
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
