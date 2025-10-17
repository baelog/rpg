#include "unity.h"
#include "../../network/protocol/message.h"
#include "testPackets.h"

void test_SequencesCreate(void) {
	struct sequences *sequences = NULL;
	struct packet pckt = { 0 };
	
    for (int i = 0; i < 2; i++) {
        pckt.sequenceID = i;
        for (int j = 0; j < MAX_PCKT; ++j) {
            pckt.packetID = j;
            pckt.packetNb = MAX_PCKT;
            addToPlace(&sequences, &pckt);
        }
    }

	TEST_ASSERT_EQUAL(2, countSquences(sequences));

    for (int i = 0; i < 2; i++) {
        pckt.sequenceID = i;
        for (int j = 0; j < MAX_PCKT; ++j) {
            pckt.packetID = j;
            pckt.packetNb = MAX_PCKT;
            addToPlace(&sequences, &pckt);
        }
    }

	TEST_ASSERT_EQUAL(2, countSquences(sequences));

    TEST_ASSERT_EQUAL(MAX_PCKT, allSamePacketInSequences(sequences));

	// pckt.packetID = 5;

	// TEST_ASSERT_EQUAL(10, countPacket(packets));
}