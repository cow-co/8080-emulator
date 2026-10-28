#include "unity.h"
#include "state.h"
#include "opcodes.h"

void setUp() {}
void tearDown() {}

void test_flags() {
    reset_state();
    TEST_ASSERT_EQUAL_UINT8(2, flags());

    reset_state();
    processorState.carry = true;
    TEST_ASSERT_EQUAL_UINT8(3, flags());

    reset_state();
    processorState.parity = true;
    TEST_ASSERT_EQUAL_UINT8(6, flags());

    reset_state();
    processorState.auxCarry = true;
    TEST_ASSERT_EQUAL_UINT8(18, flags());

    reset_state();
    processorState.zero = true;
    TEST_ASSERT_EQUAL_UINT8(66, flags());

    reset_state();
    processorState.sign = true;
    TEST_ASSERT_EQUAL_UINT8(130, flags());

    reset_state();
    processorState.carry = true;
    processorState.parity = true;
    processorState.auxCarry = true;
    processorState.zero = true;
    processorState.sign = true;
    TEST_ASSERT_EQUAL_UINT8(215, flags());
}

void test_resetState() {
    processorState.B = UINT8_MAX;
    processorState.D = UINT8_MAX;
    processorState.H = UINT8_MAX;
    processorState.A = UINT8_MAX;
    processorState.C = UINT8_MAX;
    processorState.E = UINT8_MAX;
    processorState.L = UINT8_MAX;
    processorState.readWriteMemory[0] = 10;
    processorState.readOnlyMemory[0] = 10;
    reset_state();
    TEST_ASSERT_EQUAL_UINT8(0, processorState.A);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.B);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.C);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.D);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.E);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.H);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.L);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.readWriteMemory[0]);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.readOnlyMemory[0]);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_flags);
    RUN_TEST(test_resetState);

    return UNITY_END();
}