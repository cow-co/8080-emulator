#include "unity.h"
#include "emulator_api.h"
#include "emulator_state.h"
#include "opcodes.h"

void setUp() {}
void tearDown() {}

// NOTE: Test cases largely come from the 8080 manual examples

void test_flags() {
    reset_state();
    TEST_ASSERT_EQUAL_UINT8(2, flags(&state));

    reset_state();
    state.carry = true;
    TEST_ASSERT_EQUAL_UINT8(3, flags(&state));

    reset_state();
    state.parity = true;
    TEST_ASSERT_EQUAL_UINT8(6, flags(&state));

    reset_state();
    state.auxCarry = true;
    TEST_ASSERT_EQUAL_UINT8(18, flags(&state));

    reset_state();
    state.zero = true;
    TEST_ASSERT_EQUAL_UINT8(66, flags(&state));

    reset_state();
    state.sign = true;
    TEST_ASSERT_EQUAL_UINT8(130, flags(&state));

    reset_state();
    state.carry = true;
    state.parity = true;
    state.auxCarry = true;
    state.zero = true;
    state.sign = true;
    TEST_ASSERT_EQUAL_UINT8(215, flags(&state));
}

void test_resetState() {
    state.B = UINT8_MAX;
    state.D = UINT8_MAX;
    state.H = UINT8_MAX;
    state.A = UINT8_MAX;
    state.C = UINT8_MAX;
    state.E = UINT8_MAX;
    state.L = UINT8_MAX;
    state.memory[0] = 10;
    reset_state();
    TEST_ASSERT_EQUAL_UINT8(0, state.A);
    TEST_ASSERT_EQUAL_UINT8(0, state.B);
    TEST_ASSERT_EQUAL_UINT8(0, state.C);
    TEST_ASSERT_EQUAL_UINT8(0, state.D);
    TEST_ASSERT_EQUAL_UINT8(0, state.E);
    TEST_ASSERT_EQUAL_UINT8(0, state.H);
    TEST_ASSERT_EQUAL_UINT8(0, state.L);
    TEST_ASSERT_EQUAL_UINT8(0, state.memory[0]);
}

void test_rotates() {
    reset_state();
    state.A = 0b11110010;
    rlc(&state);
    TEST_ASSERT(state.carry);
    TEST_ASSERT_EQUAL_UINT8(0b11100101, state.A);

    reset_state();
    state.A = 0b00000010;
    rlc(&state);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT_EQUAL_UINT8(0b00000100, state.A);

    reset_state();
    state.A = 0b11110010;
    rrc(&state);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT_EQUAL_UINT8(0b01111001, state.A);

    reset_state();
    state.A = 0b11110011;
    rrc(&state);
    TEST_ASSERT(state.carry);
    TEST_ASSERT_EQUAL_UINT8(0b11111001, state.A);
}

void test_stackOps() {
    // Testing one of each should be sufficient, since they all call to the main
    // push/pop implementation
    reset_state();
    state.stackPointer = 0x13A6;
    state.B = 0x6A;
    state.C = 0x30;
    push_b(&state);
    TEST_ASSERT_EQUAL_UINT16(0x13A4, state.stackPointer);
    TEST_ASSERT_EQUAL_UINT8(0x6A, state.B);
    TEST_ASSERT_EQUAL_UINT8(0x30, state.C);
    TEST_ASSERT_EQUAL_UINT8(0x6A, state.memory[0x13A5]);
    TEST_ASSERT_EQUAL_UINT8(0x30, state.memory[0x13A4]);
    TEST_ASSERT_EQUAL_UINT8(0, state.memory[0x13A6]);

    reset_state();
    state.stackPointer = 0x1508;
    state.memory[0x1508] = 0x33;
    state.memory[0x1509] = 0x0B;
    state.H = 0xFF;
    state.L = 0xFF;
    pop_h(&state);
    TEST_ASSERT_EQUAL_UINT16(0x150A, state.stackPointer);
    TEST_ASSERT_EQUAL_UINT8(0x0B, state.H);
    TEST_ASSERT_EQUAL_UINT8(0x33, state.L);
}

void test_arithmetic() {
    // DCX
    reset_state();
    state.H = 0x98;
    state.L = 0x00;
    dcx_h(&state);
    TEST_ASSERT_EQUAL_UINT8(0x97, state.H);
    TEST_ASSERT_EQUAL_UINT8(0xFF, state.L);
    
    // INX
    reset_state();
    state.D = 0x38;
    state.E = 0xFF;
    inx_d(&state);
    TEST_ASSERT_EQUAL_UINT8(0x39, state.D);
    TEST_ASSERT_EQUAL_UINT8(0x00, state.E);
    
    reset_state();
    state.stackPointer = 0xFFFF;
    inx_sp(&state);
    TEST_ASSERT_EQUAL_UINT16(0x0000, state.stackPointer);

    // INR
    reset_state();
    state.C = 0x99;
    inr_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x9A, state.C);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.parity);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(!state.zero);

    reset_state();
    state.C = 0xFF;
    inr_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x00, state.C);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(state.parity);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(state.zero);

    reset_state();
    state.C = 0x00;
    inr_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x01, state.C);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.parity);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(!state.zero);

    // DCR
    reset_state();
    state.C = 0x99;
    dcr_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x98, state.C);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.parity);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(!state.zero);

    reset_state();
    state.C = 0x00;
    dcr_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0xFF, state.C);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(state.parity);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(!state.zero);

    reset_state();
    state.C = 0x01;
    dcr_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x00, state.C);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.parity);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(state.zero);

    reset_state();
    state.H = 0x3A;
    state.L = 0x7C;
    state.memory[0x3A7C] = 0x40;
    dcr_m(&state);
    TEST_ASSERT_EQUAL_UINT8(0x3F, state.memory[0x3A7C]);

    // ADD
    reset_state();
    state.A = 0x6C;
    state.D = 0x2E;
    add_d(&state);
    TEST_ASSERT_EQUAL_UINT8(0x9A, state.A);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.parity);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(state.auxCarry);

    reset_state();
    state.A = 0x08;
    add_a(&state);
    TEST_ASSERT_EQUAL_UINT8(0x10, state.A);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.parity);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(state.auxCarry);

    reset_state();
    state.A = 0x56;
    state.memory[1] = -66;
    state.memory[2] = (uint8_t)0xCE;
    state.memory[3] = 66;
    aci(&state);
    TEST_ASSERT_EQUAL_UINT8(0x14, state.A);
    TEST_ASSERT(state.carry);
    aci(&state);
    TEST_ASSERT_EQUAL_UINT8(0x57, state.A);
    TEST_ASSERT(!state.carry);

    reset_state();
    state.B = 0x33;
    state.C = 0x9F;
    state.H = 0xA1;
    state.L = 0x7B;
    dad_b(&state);
    TEST_ASSERT_EQUAL_UINT8(0xD5, state.H);
    TEST_ASSERT_EQUAL_UINT8(0x1A, state.L);
    TEST_ASSERT(!state.carry);

    state.H = 0xFF;
    state.L = 0x00;
    dad_h(&state);
    TEST_ASSERT_EQUAL_UINT8(0b11111110, state.H);
    TEST_ASSERT_EQUAL_UINT8(0, state.L);
    TEST_ASSERT(state.carry);

    reset_state();
    state.A = 0x42;
    state.C = 0x3D;
    adc_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x7F, state.A);

    reset_state();
    state.A = 0x42;
    state.C = 0x3D;
    state.carry = true;
    adc_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x80, state.A);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(state.auxCarry);

    // SUB
    reset_state();
    state.A = 0x3E;
    sub_a(&state);
    TEST_ASSERT_EQUAL_UINT8(0, state.A);
    TEST_ASSERT(state.zero);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(state.parity);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.auxCarry);

    reset_state();
    state.A = 10;
    state.B = 9;
    sub_b(&state);
    TEST_ASSERT_EQUAL_UINT8(1, state.A);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(!state.parity);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.auxCarry);

    reset_state();
    state.B = 10;
    state.A = 9;
    sub_b(&state);
    TEST_ASSERT_EQUAL_UINT8(0xFF, state.A);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(state.parity);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(!state.auxCarry);

    reset_state();
    state.L = 2;
    state.A = 4;
    state.carry = true;
    sbb_l(&state);
    TEST_ASSERT_EQUAL_UINT8(1, state.A);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.auxCarry);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.parity);
    TEST_ASSERT(!state.sign);

    reset_state();
    state.memory[1] = 1;
    sui(&state);
    TEST_ASSERT_EQUAL_UINT8(-1, state.A);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.auxCarry);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(state.parity);

    reset_state();
    state.memory[1] = 1;
    sbi(&state);
    TEST_ASSERT_EQUAL_UINT8(-1, state.A);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.auxCarry);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(state.parity);

    reset_state();
    state.memory[1] = 1;
    state.carry = true;
    sbi(&state);
    TEST_ASSERT_EQUAL_UINT8(-2, state.A);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.auxCarry);
    TEST_ASSERT(state.sign);
    TEST_ASSERT(!state.parity);
}

void test_logic() {
    // ANA
    reset_state();
    state.A = 0xFC;
    state.C = 0x0F;
    ana_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x0C, state.A);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(state.parity);

    // XRA
    reset_state();
    state.A = 0xFC;
    xra_a(&state);
    TEST_ASSERT_EQUAL_UINT8(0x00, state.A);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.zero);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(state.parity);

    reset_state();
    state.A = 0xFF;
    state.B = 0xF0;
    xra_b(&state);
    TEST_ASSERT_EQUAL_UINT8(0x0F, state.A);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(state.parity);

    // ORA
    reset_state();
    state.C = 0x0F;
    state.A = 0x33;
    ora_c(&state);
    TEST_ASSERT_EQUAL_UINT8(0x3F, state.A);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.zero);
    TEST_ASSERT(!state.sign);
    TEST_ASSERT(state.parity);

    // CMP
    reset_state();
    state.A = 0x0A;
    state.E = 0x05;
    cmp_e(&state);
    TEST_ASSERT_EQUAL_UINT8(0x0A, state.A);
    TEST_ASSERT_EQUAL_UINT8(0x05, state.E);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.zero);

    reset_state();
    state.A = 0x02;
    state.E = 0x05;
    cmp_e(&state);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(!state.zero);

    reset_state();
    state.A = -0x1B;
    state.E = 0x05;
    cmp_e(&state);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(!state.zero);

    reset_state();
    state.A = 0x05;
    state.E = 0x05;
    cmp_e(&state);
    TEST_ASSERT(!state.carry);
    TEST_ASSERT(state.zero);
}

void test_accumulator() {
    reset_state();
    state.A = 0b10011011;
    daa(&state);
    TEST_ASSERT_EQUAL_UINT8(0x01, state.A);
    TEST_ASSERT(state.carry);
    TEST_ASSERT(state.auxCarry);

    reset_state();
    state.A = 0x51;
    cma(&state);
    TEST_ASSERT_EQUAL_UINT8(0xAE, state.A);
}

void test_utils() {
    reset_state();
    write_memory(&state, 0, 1);
    TEST_ASSERT_EQUAL_UINT8(0, state.memory[0]);
    write_memory(&state, 2048, 1);
    TEST_ASSERT_EQUAL_UINT8(1, state.memory[2048]);

    reset_state();
    set_bit_on_input_port(0, 0);
    TEST_ASSERT_EQUAL_UINT8(1, state.inputData[0]);

    reset_state();
    set_bit_on_input_port(4, 1);
    TEST_ASSERT_EQUAL_UINT8(2, state.inputData[4]);

    reset_state();
    set_bit_on_input_port(7, 7);
    TEST_ASSERT_EQUAL_UINT8(128, state.inputData[7]);

    reset_state();
    set_bit_on_input_port(7, 8);
    TEST_ASSERT_EQUAL_UINT8(128, state.inputData[7]);
    set_bit_on_input_port(7, 3);
    TEST_ASSERT_EQUAL_UINT8(136, state.inputData[7]);

    reset_state();
    set_input_port(0, 0xFF);
    unset_bit_on_input_port(0, 0);
    TEST_ASSERT_EQUAL_UINT8(254, state.inputData[0]);

    reset_state();
    set_input_port(4, 0xFF);
    unset_bit_on_input_port(4, 1);
    TEST_ASSERT_EQUAL_UINT8(253, state.inputData[4]);

    reset_state();
    set_input_port(7, 0xFF);
    unset_bit_on_input_port(7, 7);
    TEST_ASSERT_EQUAL_UINT8(127, state.inputData[7]);

    reset_state();
    set_input_port(7, 0xFF);
    unset_bit_on_input_port(7, 8);
    TEST_ASSERT_EQUAL_UINT8(127, state.inputData[7]);

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