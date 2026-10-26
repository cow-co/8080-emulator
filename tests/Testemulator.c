#include "unity.h"
#include "state.h"

void setUp() {}
void tearDown() {}


void test_RegPairs() {
    reset_state();
    TEST_ASSERT_EQUAL_UINT16(0, B_register_pair());
    TEST_ASSERT_EQUAL_UINT16(0, D_register_pair());
    TEST_ASSERT_EQUAL_UINT16(0, H_register_pair());
    TEST_ASSERT_EQUAL_UINT16(0, psw());

    processorState.B = 1;
    processorState.D = 1;
    processorState.H = 1;
    processorState.A = 1;
    TEST_ASSERT_EQUAL_UINT16(256, B_register_pair());
    TEST_ASSERT_EQUAL_UINT16(256, D_register_pair());
    TEST_ASSERT_EQUAL_UINT16(256, H_register_pair());
    TEST_ASSERT_EQUAL_UINT16(256, psw());

    reset_state();
    processorState.C = 1;
    processorState.E = 1;
    processorState.L = 1;
    processorState.flags = 1;
    TEST_ASSERT_EQUAL_UINT16(1, B_register_pair());
    TEST_ASSERT_EQUAL_UINT16(1, D_register_pair());
    TEST_ASSERT_EQUAL_UINT16(1, H_register_pair());
    TEST_ASSERT_EQUAL_UINT16(1, psw());

    reset_state();
    processorState.B = 1;
    processorState.D = 1;
    processorState.H = 1;
    processorState.A = 1;
    processorState.C = 1;
    processorState.E = 1;
    processorState.L = 1;
    processorState.flags = 1;
    TEST_ASSERT_EQUAL_UINT16(257, B_register_pair());
    TEST_ASSERT_EQUAL_UINT16(257, D_register_pair());
    TEST_ASSERT_EQUAL_UINT16(257, H_register_pair());
    TEST_ASSERT_EQUAL_UINT16(257, psw());

    reset_state();
    processorState.B = UINT8_MAX;
    processorState.D = UINT8_MAX;
    processorState.H = UINT8_MAX;
    processorState.A = UINT8_MAX;
    processorState.C = UINT8_MAX;
    processorState.E = UINT8_MAX;
    processorState.L = UINT8_MAX;
    processorState.flags = UINT8_MAX;
    TEST_ASSERT_EQUAL_UINT16(UINT16_MAX, B_register_pair());
    TEST_ASSERT_EQUAL_UINT16(UINT16_MAX, D_register_pair());
    TEST_ASSERT_EQUAL_UINT16(UINT16_MAX, H_register_pair());
    TEST_ASSERT_EQUAL_UINT16(UINT16_MAX, psw());
}

void test_FlagOps() {
    reset_state();
    set_flag(0);
    TEST_ASSERT_EQUAL_UINT8(1, processorState.flags);

    reset_state();
    set_flag(4);
    TEST_ASSERT_EQUAL_UINT8(16, processorState.flags);

    reset_state();
    set_flag(0);
    set_flag(3);
    TEST_ASSERT_EQUAL_UINT8(9, processorState.flags);

    reset_state();
    set_flag(6);
    TEST_ASSERT_EQUAL_UINT8(16, processorState.flags);

    reset_state();
    set_flag(0);
    set_flag(3);
    reset_flag(0);
    TEST_ASSERT_EQUAL_UINT8(8, processorState.flags);
}

void test_resetState() {
    processorState.B = UINT8_MAX;
    processorState.D = UINT8_MAX;
    processorState.H = UINT8_MAX;
    processorState.A = UINT8_MAX;
    processorState.C = UINT8_MAX;
    processorState.E = UINT8_MAX;
    processorState.L = UINT8_MAX;
    processorState.flags = UINT8_MAX;
    processorState.readWriteMemory[0] = 10;
    reset_state();
    TEST_ASSERT_EQUAL_UINT8(0, processorState.A);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.B);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.C);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.D);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.E);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.H);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.L);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.flags);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.readWriteMemory[0]);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_RegPairs);
    RUN_TEST(test_FlagOps);
    RUN_TEST(test_resetState);

    return UNITY_END();
}