#include <catch2/catch_test_macros.hpp>
#include "testPacket.h"



TEST_CASE( "Add packets in order" ) {
    struct packetList *packets = NULL;
	struct packet pckt;
	
    memset(&pckt, 0, sizeof(pckt));

	for (int i = 0; i < 10; ++i) {
        pckt.packetID = i;
		insertPacket(&packets, &pckt);
	}

    REQUIRE( countPacket(packets) == 10 );
	

    for (int i = 0; i < 5; ++i) {
        pckt.packetID = i;
        insertPacket(&packets, &pckt);
    }
    REQUIRE( countPacket(packets) == 10 );

    REQUIRE( arePacketInOrder(packets) == 0 );

    clearPackets(&packets);

    REQUIRE( countPacket(packets) == 0 );


}

TEST_CASE( "Add packets in reverse order" ) {
    struct packetList *packets = NULL;
	struct packet pckt;
	
    memset(&pckt, 0, sizeof(pckt));

	for (int i = 10; i > 0; --i) {
        pckt.packetID = i;
		insertPacket(&packets, &pckt);
	}
    // exit(0);

    REQUIRE( countPacket(packets) == 10 );
	
    // pckt.packetID = 5;

    for (int i = 5; i > 0; --i) {
        pckt.packetID = i;
        insertPacket(&packets, &pckt);
    }
    REQUIRE( countPacket(packets) == 10 );

    REQUIRE( arePacketInOrder(packets) == 0 );


    clearPackets(&packets);

    REQUIRE( countPacket(packets) == 0 );


}

TEST_CASE( "Add packets in shuffle mode" ) {
    struct packetList *packets = NULL;
	struct packet pckt;
	int shuffle[] = {5, 1, 4, 0, 9, 3, 2, 8, 7, 6};
    memset(&pckt, 0, sizeof(pckt));

	for (int i = 0; i < 10; ++i) {
        pckt.packetID = shuffle[i];
		insertPacket(&packets, &pckt);
	}

    REQUIRE( countPacket(packets) == 10 );
	

    for (int i = 5; i > 0; --i) {
        pckt.packetID = i;
        insertPacket(&packets, &pckt);
    }
    REQUIRE( countPacket(packets) == 10 );

    REQUIRE( arePacketInOrder(packets) == 0 );


    clearPackets(&packets);

    REQUIRE( countPacket(packets) == 0 );


}


TEST_CASE( "test on sequences" ) {
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

	REQUIRE(countSquences(sequences) == 2);

    for (int i = 0; i < 2; i++) {
        pckt.sequenceID = i;
        for (int j = 0; j < MAX_PCKT; ++j) {
            pckt.packetID = j;
            pckt.packetNb = MAX_PCKT;
            addToPlace(&sequences, &pckt);
        }
    }

	REQUIRE(countSquences(sequences) == 2);

    REQUIRE(allSamePacketInSequences(sequences) == MAX_PCKT);

    clearSquences(&sequences);

	// pckt.packetID = 5;

	// TEST_ASSERT_EQUAL(10, countPacket(packets));
}
