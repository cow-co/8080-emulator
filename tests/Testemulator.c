#include "unity.h"
#include "emulator_layer.h"
#include "state.h"
#include "opcodes.h"

void setUp() {}
void tearDown() {}

// NOTE: Test cases largely come from the 8080 manual examples

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
    reset_state();
    TEST_ASSERT_EQUAL_UINT8(0, processorState.A);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.B);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.C);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.D);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.E);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.H);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.L);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.readWriteMemory[0]);
}

void test_rotates() {
    reset_state();
    processorState.A = 0b11110010;
    rlc();
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT_EQUAL_UINT8(0b11100101, processorState.A);

    reset_state();
    processorState.A = 0b00000010;
    rlc();
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT_EQUAL_UINT8(0b00000100, processorState.A);

    reset_state();
    processorState.A = 0b11110010;
    rrc();
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT_EQUAL_UINT8(0b01111001, processorState.A);

    reset_state();
    processorState.A = 0b11110011;
    rrc();
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT_EQUAL_UINT8(0b11111001, processorState.A);
}

void test_stackOps() {
    // Testing one of each should be sufficient, since they all call to the main
    // push/pop implementation
    reset_state();
    processorState.stackPointer = 0x13A6;
    processorState.B = 0x6A;
    processorState.C = 0x30;
    push_b();
    TEST_ASSERT_EQUAL_UINT16(0x13A4, processorState.stackPointer);
    TEST_ASSERT_EQUAL_UINT8(0x6A, processorState.B);
    TEST_ASSERT_EQUAL_UINT8(0x30, processorState.C);
    TEST_ASSERT_EQUAL_UINT8(0x6A, processorState.readWriteMemory[0x13A5]);
    TEST_ASSERT_EQUAL_UINT8(0x30, processorState.readWriteMemory[0x13A4]);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.readWriteMemory[0x13A6]);

    reset_state();
    processorState.stackPointer = 0x1508;
    processorState.readWriteMemory[0x1508] = 0x33;
    processorState.readWriteMemory[0x1509] = 0x0B;
    processorState.H = 0xFF;
    processorState.L = 0xFF;
    pop_h();
    TEST_ASSERT_EQUAL_UINT16(0x150A, processorState.stackPointer);
    TEST_ASSERT_EQUAL_UINT8(0x0B, processorState.H);
    TEST_ASSERT_EQUAL_UINT8(0x33, processorState.L);
}

void test_arithmetic() {
    // DCX
    reset_state();
    processorState.H = 0x98;
    processorState.L = 0x00;
    dcx_h();
    TEST_ASSERT_EQUAL_UINT8(0x97, processorState.H);
    TEST_ASSERT_EQUAL_UINT8(0xFF, processorState.L);
    
    // INX
    reset_state();
    processorState.D = 0x38;
    processorState.E = 0xFF;
    inx_d();
    TEST_ASSERT_EQUAL_UINT8(0x39, processorState.D);
    TEST_ASSERT_EQUAL_UINT8(0x00, processorState.E);
    
    reset_state();
    processorState.stackPointer = 0xFFFF;
    inx_sp();
    TEST_ASSERT_EQUAL_UINT16(0x0000, processorState.stackPointer);

    // INR
    reset_state();
    processorState.C = 0x99;
    inr_c();
    TEST_ASSERT_EQUAL_UINT8(0x9A, processorState.C);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.parity);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(!processorState.zero);

    reset_state();
    processorState.C = 0xFF;
    inr_c();
    TEST_ASSERT_EQUAL_UINT8(0x00, processorState.C);
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(processorState.parity);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(processorState.zero);

    reset_state();
    processorState.C = 0x00;
    inr_c();
    TEST_ASSERT_EQUAL_UINT8(0x01, processorState.C);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.parity);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(!processorState.zero);

    // DCR
    reset_state();
    processorState.C = 0x99;
    dcr_c();
    TEST_ASSERT_EQUAL_UINT8(0x98, processorState.C);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.parity);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(!processorState.zero);

    reset_state();
    processorState.C = 0x00;
    dcr_c();
    TEST_ASSERT_EQUAL_UINT8(0xFF, processorState.C);
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(processorState.parity);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(!processorState.zero);

    reset_state();
    processorState.C = 0x01;
    dcr_c();
    TEST_ASSERT_EQUAL_UINT8(0x00, processorState.C);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.parity);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(processorState.zero);

    reset_state();
    processorState.H = 0x3A;
    processorState.L = 0x7C;
    processorState.readWriteMemory[0x3A7C] = 0x40;
    dcr_m();
    TEST_ASSERT_EQUAL_UINT8(0x3F, processorState.readWriteMemory[0x3A7C]);

    // ADD
    reset_state();
    processorState.A = 0x6C;
    processorState.D = 0x2E;
    add_d();
    TEST_ASSERT_EQUAL_UINT8(0x9A, processorState.A);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.parity);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(processorState.auxCarry);

    reset_state();
    processorState.A = 0x08;
    add_a();
    TEST_ASSERT_EQUAL_UINT8(0x10, processorState.A);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.parity);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(processorState.auxCarry);

    reset_state();
    processorState.A = 0x56;
    processorState.readWriteMemory[1] = -66;
    processorState.readWriteMemory[2] = (uint8_t)0xCE;
    processorState.readWriteMemory[3] = 66;
    aci();
    TEST_ASSERT_EQUAL_UINT8(0x14, processorState.A);
    TEST_ASSERT(processorState.carry);
    aci();
    TEST_ASSERT_EQUAL_UINT8(0x57, processorState.A);
    TEST_ASSERT(!processorState.carry);

    reset_state();
    processorState.B = 0x33;
    processorState.C = 0x9F;
    processorState.H = 0xA1;
    processorState.L = 0x7B;
    dad_b();
    TEST_ASSERT_EQUAL_UINT8(0xD5, processorState.H);
    TEST_ASSERT_EQUAL_UINT8(0x1A, processorState.L);
    TEST_ASSERT(!processorState.carry);

    processorState.H = 0xFF;
    processorState.L = 0x00;
    dad_h();
    TEST_ASSERT_EQUAL_UINT8(0b11111110, processorState.H);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.L);
    TEST_ASSERT(processorState.carry);

    reset_state();
    processorState.A = 0x42;
    processorState.C = 0x3D;
    adc_c();
    TEST_ASSERT_EQUAL_UINT8(0x7F, processorState.A);

    reset_state();
    processorState.A = 0x42;
    processorState.C = 0x3D;
    processorState.carry = true;
    adc_c();
    TEST_ASSERT_EQUAL_UINT8(0x80, processorState.A);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(processorState.auxCarry);

    // SUB
    reset_state();
    processorState.A = 0x3E;
    sub_a();
    TEST_ASSERT_EQUAL_UINT8(0, processorState.A);
    TEST_ASSERT(processorState.zero);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(processorState.parity);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.auxCarry);

    reset_state();
    processorState.A = 10;
    processorState.B = 9;
    sub_b();
    TEST_ASSERT_EQUAL_UINT8(1, processorState.A);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(!processorState.parity);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.auxCarry);

    reset_state();
    processorState.B = 10;
    processorState.A = 9;
    sub_b();
    TEST_ASSERT_EQUAL_UINT8(0xFF, processorState.A);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(processorState.parity);
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(!processorState.auxCarry);

    reset_state();
    processorState.L = 2;
    processorState.A = 4;
    processorState.carry = true;
    sbb_l();
    TEST_ASSERT_EQUAL_UINT8(1, processorState.A);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.auxCarry);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.parity);
    TEST_ASSERT(!processorState.sign);

    reset_state();
    processorState.readWriteMemory[1] = 1;
    sui();
    TEST_ASSERT_EQUAL_UINT8(-1, processorState.A);
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.auxCarry);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(processorState.parity);

    reset_state();
    processorState.readWriteMemory[1] = 1;
    sbi();
    TEST_ASSERT_EQUAL_UINT8(-1, processorState.A);
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.auxCarry);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(processorState.parity);

    reset_state();
    processorState.readWriteMemory[1] = 1;
    processorState.carry = true;
    sbi();
    TEST_ASSERT_EQUAL_UINT8(-2, processorState.A);
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.auxCarry);
    TEST_ASSERT(processorState.sign);
    TEST_ASSERT(!processorState.parity);
}

void test_logic() {
    // ANA
    reset_state();
    processorState.A = 0xFC;
    processorState.C = 0x0F;
    ana_c();
    TEST_ASSERT_EQUAL_UINT8(0x0C, processorState.A);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(processorState.parity);

    // XRA
    reset_state();
    processorState.A = 0xFC;
    xra_a();
    TEST_ASSERT_EQUAL_UINT8(0x00, processorState.A);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.zero);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(processorState.parity);

    reset_state();
    processorState.A = 0xFF;
    processorState.B = 0xF0;
    xra_b();
    TEST_ASSERT_EQUAL_UINT8(0x0F, processorState.A);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(processorState.parity);

    // ORA
    reset_state();
    processorState.C = 0x0F;
    processorState.A = 0x33;
    ora_c();
    TEST_ASSERT_EQUAL_UINT8(0x3F, processorState.A);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.zero);
    TEST_ASSERT(!processorState.sign);
    TEST_ASSERT(processorState.parity);

    // CMP
    reset_state();
    processorState.A = 0x0A;
    processorState.E = 0x05;
    cmp_e();
    TEST_ASSERT_EQUAL_UINT8(0x0A, processorState.A);
    TEST_ASSERT_EQUAL_UINT8(0x05, processorState.E);
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.zero);

    reset_state();
    processorState.A = 0x02;
    processorState.E = 0x05;
    cmp_e();
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(!processorState.zero);

    reset_state();
    processorState.A = -0x1B;
    processorState.E = 0x05;
    cmp_e();
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(!processorState.zero);

    reset_state();
    processorState.A = 0x05;
    processorState.E = 0x05;
    cmp_e();
    TEST_ASSERT(!processorState.carry);
    TEST_ASSERT(processorState.zero);
}

void test_accumulator() {
    reset_state();
    processorState.A = 0b10011011;
    daa();
    TEST_ASSERT_EQUAL_UINT8(0x01, processorState.A);
    TEST_ASSERT(processorState.carry);
    TEST_ASSERT(processorState.auxCarry);

    reset_state();
    processorState.A = 0x51;
    cma();
    TEST_ASSERT_EQUAL_UINT8(0xAE, processorState.A);
}

void test_utils() {
    reset_state();
    write_memory(0, 1);
    TEST_ASSERT_EQUAL_UINT8(0, processorState.readWriteMemory[0]);
    write_memory(2048, 1);
    TEST_ASSERT_EQUAL_UINT8(1, processorState.readWriteMemory[2048]);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_flags);
    RUN_TEST(test_resetState);
    RUN_TEST(test_accumulator);
    RUN_TEST(test_arithmetic);
    RUN_TEST(test_rotates);
    RUN_TEST(test_stackOps);
    RUN_TEST(test_logic);
    RUN_TEST(test_utils);

    return UNITY_END();
}