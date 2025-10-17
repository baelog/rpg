#include "unity.h"
#include "../../network/protocol/message.h"
#include "testPackets.h"


void test_PacketsAdd(void) {
	struct packetList *packets = NULL;
	struct packet pckt = { 0 };
	
	for (int i = 0; i < 10; ++i) {
		pckt.packetID = i;
		insertPacket(&packets, &pckt);
	}

	TEST_ASSERT_EQUAL(10, countPacket(packets));

	pckt.packetID = 5;

	TEST_ASSERT_EQUAL(10, countPacket(packets));
}
