#include "unity.h"
#include "../network/protocol/message.h"
#include "packets/testPackets.h"

// int add(int a, int b);

void setUp(void)
{
  /* This is run before EACH TEST */
  //Counter = 0x5a5a;
}

void tearDown(void)
{
}

// void test_AddFuncion(void) {
// 	TEST_ASSERT_EQUAL(3, add(1, 2));
// 	TEST_ASSERT_EQUAL(4, add(1, 2));
// }


int main(void)
{
  UnityBegin("MaincTest.c");
  RUN_TEST(test_PacketsAdd, __LINE__);

  RUN_TEST(test_SequencesCreate, __LINE__);

  return (UnityEnd());
}
