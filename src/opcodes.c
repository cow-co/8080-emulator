#include "opcodes.h"
#include "state.h"

uint16_t form_2_byte_from_1_bytes(const uint8_t highRegister, const uint8_t lowRegister) {
    uint16_t result = (uint16_t)highRegister << 8;
    result |= (uint16_t)lowRegister;
    return result;
}

void assign_parity(unsigned value, size_t size) {
    unsigned par = 0;
    value = (value & ((1 << size) - 1));
    for (size_t i = 0; i < size; ++i) {
        if (value & 0x01) {
            ++par;
        }
        value = value >> 1;
    }
    processorState.parity = !(par & 0x01);
}

void nop() {
    processorState.programCounter += 1;
}

/////////////////////////////////////////// LXI ///////////////////////////////////////////

void lxi(uint8_t* const highRegister, uint8_t* const lowRegister) {
    // Load extended immediate
    *highRegister = processorState.readWriteMemory[processorState.programCounter + 2];
    *lowRegister = processorState.readWriteMemory[processorState.programCounter + 1];
    processorState.programCounter += 3;
}

void lxi_b() {
    lxi(&processorState.B, &processorState.C);
}

void lxi_d() {
    lxi(&processorState.D, &processorState.E);
}

void lxi_h() {
    lxi(&processorState.H, &processorState.L);
}

void lxi_sp() {
    processorState.stackPointer = ((uint16_t)processorState.readWriteMemory[processorState.programCounter + 2]) << 8;
    processorState.stackPointer |= (uint16_t)processorState.readWriteMemory[processorState.programCounter + 1];
    processorState.programCounter += 3;
}

/////////////////////////////////////////// MVI ///////////////////////////////////////////

void mvi(uint8_t* const dst) {
    // Move an immediate
    *dst = processorState.readOnlyMemory[processorState.programCounter + 1];
    processorState.programCounter += 2;
}

void mvi_b() {
    mvi(&processorState.B);
}

void mvi_c() {
    mvi(&processorState.C);
}

void mvi_d() {
    mvi(&processorState.D);
}

void mvi_e() {
    mvi(&processorState.E);
}

void mvi_h() {
    mvi(&processorState.H);
}

void mvi_l() {
    mvi(&processorState.L);
}

void mvi_a() {
    mvi(&processorState.A);
}

void mvi_m() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mvi(&processorState.readWriteMemory[addr]);
}

/////////////////////////////////////////// MOV ///////////////////////////////////////////

void mov(uint8_t* const dst, uint8_t* const src) {
    *dst = *src;
    ++processorState.programCounter;
}

void mov_bc() {
    mov(&processorState.B, &processorState.C);
}
void mov_bd() {
    mov(&processorState.B, &processorState.D);
}
void mov_be() {
    mov(&processorState.B, &processorState.E);
}
void mov_bh() {
    mov(&processorState.B, &processorState.H);
}
void mov_bl() {
    mov(&processorState.B, &processorState.L);
}
void mov_bm() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.B, &processorState.readWriteMemory[addr]);
}
void mov_ba() {
    mov(&processorState.B, &processorState.A);
}

void mov_cb() {
    mov(&processorState.C, &processorState.B);
}
void mov_cd() {
    mov(&processorState.C, &processorState.D);
}
void mov_ce() {
    mov(&processorState.C, &processorState.E);
}
void mov_ch() {
    mov(&processorState.C, &processorState.H);
}
void mov_cl() {
    mov(&processorState.C, &processorState.L);
}
void mov_cm() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.C, &processorState.readWriteMemory[addr]);
}
void mov_ca() {
    mov(&processorState.C, &processorState.A);
}

void mov_db() {
    mov(&processorState.D, &processorState.B);
}
void mov_dc() {
    mov(&processorState.D, &processorState.C);
}
void mov_de() {
    mov(&processorState.D, &processorState.E);
}
void mov_dh() {
    mov(&processorState.D, &processorState.H);
}
void mov_dl() {
    mov(&processorState.D, &processorState.L);
}
void mov_dm() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.D, &processorState.readWriteMemory[addr]);
}
void mov_da() {
    mov(&processorState.D, &processorState.A);
}

void mov_eb() {
    mov(&processorState.E, &processorState.C);
}
void mov_ec() {
    mov(&processorState.E, &processorState.C);
}
void mov_ed() {
    mov(&processorState.E, &processorState.D);
}
void mov_eh() {
    mov(&processorState.E, &processorState.H);
}
void mov_el() {
    mov(&processorState.E, &processorState.L);
}
void mov_em() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.E, &processorState.readWriteMemory[addr]);
}
void mov_ea() {
    mov(&processorState.E, &processorState.A);
}

void mov_hb() {
    mov(&processorState.H, &processorState.C);
}
void mov_hc() {
    mov(&processorState.H, &processorState.C);
}
void mov_hd() {
    mov(&processorState.H, &processorState.D);
}
void mov_he() {
    mov(&processorState.H, &processorState.E);
}
void mov_hl() {
    mov(&processorState.H, &processorState.L);
}
void mov_hm() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.H, &processorState.readWriteMemory[addr]);
}
void mov_ha() {
    mov(&processorState.H, &processorState.A);
}

void mov_lb() {
    mov(&processorState.L, &processorState.C);
}
void mov_lc() {
    mov(&processorState.L, &processorState.C);
}
void mov_ld() {
    mov(&processorState.L, &processorState.D);
}
void mov_le() {
    mov(&processorState.L, &processorState.E);
}
void mov_lh() {
    mov(&processorState.L, &processorState.H);
}
void mov_lm() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.L, &processorState.readWriteMemory[addr]);
}
void mov_la() {
    mov(&processorState.L, &processorState.A);
}

void mov_mb() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.readWriteMemory[addr], &processorState.C);
}
void mov_mc() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.readWriteMemory[addr], &processorState.C);
}
void mov_md() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.readWriteMemory[addr], &processorState.D);
}
void mov_me() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.readWriteMemory[addr], &processorState.E);
}
void mov_mh() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.readWriteMemory[addr], &processorState.H);
}
void mov_ml() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.readWriteMemory[addr], &processorState.L);
}
void mov_ma() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.readWriteMemory[addr], &processorState.A);
}

void mov_ab() {
    mov(&processorState.A, &processorState.C);
}
void mov_ac() {
    mov(&processorState.A, &processorState.C);
}
void mov_ad() {
    mov(&processorState.A, &processorState.D);
}
void mov_ae() {
    mov(&processorState.A, &processorState.E);
}
void mov_ah() {
    mov(&processorState.A, &processorState.H);
}
void mov_al() {
    mov(&processorState.A, &processorState.L);
}
void mov_am() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    mov(&processorState.A, &processorState.readWriteMemory[addr]);
}

/////////////////////////////////////////// INR ///////////////////////////////////////////

void inr(uint8_t* const dst) {
    // TODO Assign aux carry
    uint16_t res = *dst + 1;
    processorState.carry = (res & 0b100000000);
    *dst += 1;
    processorState.zero = *dst == 0;
    assign_parity(*dst, 8);
    processorState.sign = *dst & 0b10000000;
    ++processorState.programCounter;
}

void inr_b() {
    inr(&processorState.B);
}

void inr_c() {
    inr(&processorState.C);
}

void inr_d() {
    inr(&processorState.D);
}

void inr_e() {
    inr(&processorState.E);
}

void inr_h() {
    inr(&processorState.H);
}

void inr_l() {
    inr(&processorState.L);
}

void inr_m() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    inr(&processorState.readWriteMemory[addr]);
}

void inr_a() {
    inr(&processorState.A);
}

/////////////////////////////////////////// INX ///////////////////////////////////////////

void inx(uint8_t* const highRegister, uint8_t* const lowRegister) {
    *lowRegister += 1;
    if (*lowRegister == 0) {
        *highRegister += 1;
    }
    ++processorState.programCounter;
}

void inx_b() {
    inx(&processorState.B, &processorState.C);
}

void inx_d() {
    inx(&processorState.D, &processorState.E);
}

void inx_h() {
    inx(&processorState.H, &processorState.L);
}

void inx_sp() {
    ++processorState.stackPointer;
    ++processorState.programCounter;
}

/////////////////////////////////////////// DCR ///////////////////////////////////////////

void dcr(uint8_t* const reg) {
    // TODO Assign aux carry
    uint16_t res = *reg - 1;
    processorState.carry = (res & 0b100000000);
    *reg -= 1;
    processorState.zero = *reg == 0;
    assign_parity(*reg, 8);
    processorState.sign = *reg & 0b10000000;
    ++processorState.programCounter;
}

void dcr_b() {
    dcr(&processorState.B);
}

void dcr_c() {
    dcr(&processorState.C);
}

void dcr_d() {
    dcr(&processorState.D);
}

void dcr_e() {
    dcr(&processorState.E);
}

void dcr_h() {
    dcr(&processorState.H);
}

void dcr_l() {
    dcr(&processorState.L);
}

void dcr_m() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    dcr(&processorState.readWriteMemory[addr]);
}

void dcr_a() {
    dcr(&processorState.A);
}

/////////////////////////////////////////// DCX ///////////////////////////////////////////

void dcx(uint8_t* const highRegister, uint8_t* const lowRegister) {
    *lowRegister -= 1;
    if (*lowRegister == UINT8_MAX) {
        *highRegister -= 1;
    }
    ++processorState.programCounter;
}

void dcx_b() {
    dcx(&processorState.B, &processorState.C);
}

void dcx_d() {
    dcx(&processorState.D, &processorState.E);
}

void dcx_h() {
    dcx(&processorState.H, &processorState.L);
}

void dcx_sp() {
    --processorState.stackPointer;
    ++processorState.programCounter;
}

/////////////////////////////////////// LOAD/STORE ////////////////////////////////////////

void stax_b() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.B, processorState.C);
    processorState.readWriteMemory[addr] = processorState.A;
    ++processorState.programCounter;
}

void stax_d() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.D, processorState.E);
    processorState.readWriteMemory[addr] = processorState.A;
    ++processorState.programCounter;
}

void ldax_b() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.B, processorState.C);
    processorState.A = processorState.readWriteMemory[addr];
    ++processorState.programCounter;
}

void ldax_d() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.D, processorState.E);
    processorState.A = processorState.readWriteMemory[addr];
    ++processorState.programCounter;
}

void sphl() {
    processorState.stackPointer = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    ++processorState.programCounter;
}

void sta() {
    const uint16_t addr = form_2_byte_from_1_bytes(
        processorState.readOnlyMemory[processorState.programCounter + 2],
        processorState.readOnlyMemory[processorState.programCounter + 1]
    );
    processorState.readWriteMemory[addr] = processorState.A;
    processorState.programCounter += 3;
}

void lda() {
    const uint16_t addr = form_2_byte_from_1_bytes(
        processorState.readOnlyMemory[processorState.programCounter + 2],
        processorState.readOnlyMemory[processorState.programCounter + 1]
    );
    processorState.A = processorState.readWriteMemory[addr];
    processorState.programCounter += 3;
}

void shld() {
    const uint16_t addr = form_2_byte_from_1_bytes(
        processorState.readOnlyMemory[processorState.programCounter + 2],
        processorState.readOnlyMemory[processorState.programCounter + 1]
    );
    processorState.readWriteMemory[addr] = processorState.L;
    processorState.readWriteMemory[addr + 1] = processorState.H;
    processorState.programCounter += 3;
}

void lhld() {
    const uint16_t addr = form_2_byte_from_1_bytes(
        processorState.readOnlyMemory[processorState.programCounter + 2],
        processorState.readOnlyMemory[processorState.programCounter + 1]
    );
    processorState.L = processorState.readWriteMemory[addr];
    processorState.H = processorState.readWriteMemory[addr + 1];
    processorState.programCounter += 3;
}

/////////////////////////////////////// EXCHANGE ///////////////////////////////////////

void xchg() {
    uint8_t tmp = processorState.D;
    processorState.D = processorState.H;
    processorState.H = tmp;
    tmp = processorState.E;
    processorState.E = processorState.L;
    processorState.L = tmp;
    ++processorState.programCounter;
}

void xthl() {
    uint8_t tmp = processorState.L;
    processorState.L = processorState.readWriteMemory[processorState.stackPointer];
    processorState.readWriteMemory[processorState.stackPointer] = tmp;
    tmp = processorState.H;
    processorState.H = processorState.readWriteMemory[processorState.stackPointer + 1];
    processorState.readWriteMemory[processorState.stackPointer + 1] = tmp;
    ++processorState.programCounter;
}

/////////////////////////////////////////// JUMP ///////////////////////////////////////////

void pchl() {
    // NOTE: We do not increment PC after this
    processorState.programCounter = form_2_byte_from_1_bytes(processorState.H, processorState.L);
}

void jmp() {
    // NOTE: We do not increment PC after this
    processorState.programCounter = form_2_byte_from_1_bytes(
        processorState.readOnlyMemory[processorState.programCounter + 2],
        processorState.readOnlyMemory[processorState.programCounter + 2]
    );
}

void jc() {
    if (processorState.carry) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

void jnc() {
    if (!processorState.carry) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

void jz() {
    if (processorState.zero) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

void jnz() {
    if (!processorState.zero) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

void jm() {
    if (processorState.sign) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

void jp() {
    if (!processorState.sign) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

void jpe() {
    if (processorState.parity) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

void jpo() {
    if (!processorState.parity) {
        jmp();
    } else {
        processorState.programCounter += 3;
    }
}

/////////////////////////////////////////// STACK ///////////////////////////////////////////

void push(const uint8_t highByte, const uint8_t lowByte) {
    processorState.readWriteMemory[processorState.stackPointer - 1] = highByte;
    processorState.readWriteMemory[processorState.stackPointer - 2] = lowByte;
    ++processorState.programCounter;
    processorState.stackPointer -= 2;
}

void push_b() {
    push(processorState.B, processorState.C);
}

void push_d() {
    push(processorState.D, processorState.E);
}
void push_h() {
    push(processorState.H, processorState.L);
}

void push_psw() {
    push(processorState.A, flags());
}

void pop(uint8_t* const highByte, uint8_t* const lowByte) {
    *lowByte = processorState.readWriteMemory[processorState.stackPointer];
    *highByte = processorState.readWriteMemory[processorState.stackPointer + 1];
    ++processorState.programCounter;
    processorState.stackPointer += 2;
}

void pop_b() {
    pop(&processorState.B, &processorState.C);
}

void pop_d() {
    pop(&processorState.D, &processorState.E);
}
void pop_h() {
    pop(&processorState.H, &processorState.L);
}

void pop_psw() {
    processorState.A = processorState.readWriteMemory[processorState.stackPointer];
    const uint8_t flags = processorState.readWriteMemory[processorState.stackPointer + 1];
    processorState.carry = flags & (uint8_t)1;
    processorState.parity= flags & (uint8_t)4;
    processorState.auxCarry = flags & (uint8_t)16;
    processorState.zero = flags & (uint8_t)64;
    processorState.sign = flags & (uint8_t)128;
    ++processorState.programCounter;
    processorState.stackPointer += 2;
}

/////////////////////////////////////////// ROTATE ///////////////////////////////////////////

void rlc() {
    processorState.carry = processorState.A & (uint8_t)128;
    processorState.A = processorState.A << 1;
    processorState.A |= (uint8_t)processorState.carry;
}

void rrc() {
    processorState.carry = processorState.A & (uint8_t)1;
    processorState.A = processorState.A >> 1;
    processorState.A |= ((uint8_t)processorState.carry << 7);
}

void ral() {
    const bool tmp = processorState.carry;
    processorState.carry = processorState.A & (uint8_t)128;
    processorState.A = processorState.A << 1;
    processorState.A |= (uint8_t)tmp;
}

void rar() {
    const bool tmp = processorState.carry;
    processorState.carry = processorState.A & (uint8_t)1;
    processorState.A = processorState.A >> 1;
    processorState.A |= ((uint8_t)tmp << 7);
}

/////////////////////////////////////////// CARRY BIT ///////////////////////////////////////////

void cmc() {
    processorState.carry = !processorState.carry;
    ++processorState.programCounter;
}

void stc() {
    processorState.carry = true;
    ++processorState.programCounter;
}

/////////////////////////////////////////// ACCUMULATOR ///////////////////////////////////////////

void cma() {
    processorState.A = ~processorState.A;
    ++processorState.programCounter;
}

void daa() {
    // Decimal adjust accumulator: converts accumulator into two decimal digits
    const uint8_t lowNibble = processorState.A & 0b00001111;
    const bool lowNibbleGreaterThanNine = lowNibble > 9;
    if (processorState.auxCarry || lowNibbleGreaterThanNine) {
        // Checks if the addition will generate a carry out of bit 3
        uint16_t res = lowNibble + 0b0110;
        processorState.auxCarry = (res & 0b10000);
        res = processorState.A + 6;
        processorState.carry = (res & 0b100000000);
        processorState.A += 6;
    }
    
    const uint8_t highNibble = processorState.A & 0b11110000;
    const bool highNibbleGreaterThanNine = (highNibble >> 4) > 9;
    if (processorState.carry || highNibbleGreaterThanNine) {
        // Checks if the addition will generate a carry out of bit 7
        uint16_t res = (highNibble + 0b01100000);
        processorState.carry = (res & 0b100000000);
        processorState.A += 0b01100000;
    }
    ++processorState.programCounter;
}

/////////////////////////////////////////// ARITHMETIC ///////////////////////////////////////////

// TODO Write tests for arithmetic

void add(const uint8_t value) {
    // TODO Assign aux carry
    uint16_t res = processorState.A + value;
    processorState.carry = (res & 0b100000000);
    processorState.A += value;
    processorState.zero = processorState.A == 0;
    assign_parity(processorState.A, 8);
    processorState.sign = processorState.A & 0b10000000;
    ++processorState.programCounter;
}

void add_b() {
    add(processorState.B);
}

void add_c() {
    add(processorState.C);
}

void add_d() {
    add(processorState.D);
}

void add_e() {
    add(processorState.E);
}

void add_h() {
    add(processorState.H);
}

void add_l() {
    add(processorState.L);
}

void add_m() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    add(processorState.readWriteMemory[addr]);
}

void add_a() {
    add(processorState.A);
}

/////////////////////////////////////////// LOGIC ///////////////////////////////////////////

void ana(const uint8_t value) {
    processorState.A &= value;
    processorState.carry = false;
    assign_parity(processorState.A, 8);
    processorState.zero = !processorState.A;
    processorState.sign = processorState.A & 0b10000000;
    ++processorState.programCounter;
}

void ana_b() {
    ana(processorState.B);
}

void ana_c() {
    ana(processorState.C);
}

void ana_d() {
    ana(processorState.D);
}

void ana_e() {
    ana(processorState.E);
}

void ana_h() {
    ana(processorState.H);
}

void ana_l() {
    ana(processorState.L);
}

void ana_m() {
    const uint16_t addr = form_2_byte_from_1_bytes(processorState.H, processorState.L);
    ana(processorState.readWriteMemory[addr]);
}

void ana_a() {
    ana(processorState.A);
}

void xra(const uint8_t value) {
    processorState.A ^= value;
    processorState.carry = false;
    processorState.auxCarry = false;
    assign_parity(processorState.A, 8);
    processorState.zero = !processorState.A;
    processorState.sign = processorState.A & 0b10000000;
    ++processorState.programCounter;
}

void xra_b() {
    xra(processorState.B);
}

void xra_c() {
    xra(processorState.C);
}

void xra_d() {
    xra(processorState.D);
}

void xra_e() {
    xra(processorState.E);
}

void xra_h() {
    xra(processorState.H);
}

void xra_l() {
    xra(processorState.L);
}

void xra_m() {
    xra(processorState.B);
}

void xra_a() {
    xra(processorState.A);
}

void ora(const uint8_t value) {
    processorState.A |= value;
    processorState.carry = false;
    assign_parity(processorState.A, 8);
    processorState.zero = !processorState.A;
    processorState.sign = processorState.A & 0b10000000;
    ++processorState.programCounter;
}

void ora_b() {
    ora(processorState.B);
}

void ora_c() {
    ora(processorState.C);
}

void ora_d() {
    ora(processorState.D);
}

void ora_e() {
    ora(processorState.E);
}

void ora_h() {
    ora(processorState.H);
}

void ora_l() {
    ora(processorState.L);
}

void ora_m() {
    ora(processorState.B);
}

void ora_a() {
    ora(processorState.A);
}

/////////////////////////////////////////// CALL/RET ///////////////////////////////////////////

// TODO Write tests for call/ret

void call() {
    processorState.readWriteMemory[processorState.stackPointer - 1] = (uint8_t)(processorState.programCounter >> 8);
    processorState.readWriteMemory[processorState.stackPointer - 2] = (uint8_t)(processorState.programCounter & 0xFF);
    processorState.stackPointer -= 2;
    processorState.programCounter = form_2_byte_from_1_bytes(
        processorState.readOnlyMemory[processorState.programCounter + 2],
        processorState.readOnlyMemory[processorState.programCounter + 1]
    );
}

void cc() {
    if (processorState.carry) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void cnc() {
    if (!processorState.carry) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void cz() {
    if (processorState.zero) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void cnz() {
    if (!processorState.zero) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void cm() {
    if (processorState.sign) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void cp() {
    if (!processorState.sign) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void cpe() {
    if (processorState.parity) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void cpo() {
    if (!processorState.parity) {
        call();
    } else {
        processorState.programCounter += 3;
    }
}

void ret() {
    processorState.programCounter &= (processorState.readWriteMemory[processorState.stackPointer + 1] << 8);
    processorState.programCounter &= processorState.readWriteMemory[processorState.stackPointer + 0];
}

void rc() {
    if (processorState.carry) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

void rnc() {
    if (!processorState.carry) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

void rz() {
    if (processorState.zero) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

void rnz() {
    if (!processorState.zero) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

void rm() {
    if (processorState.sign) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

void rp() {
    if (!processorState.sign) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

void rpe() {
    if (processorState.parity) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

void rpo() {
    if (!processorState.parity) {
        ret();
    } else {
        processorState.programCounter += 3;
    }
}

/////////////////////////////////////////// INTERRUPTS/RESTARTS ///////////////////////////////////////////

void rst(const uint8_t exp) {
    processorState.readWriteMemory[processorState.stackPointer - 1] = (uint8_t)(processorState.programCounter >> 8);
    processorState.readWriteMemory[processorState.stackPointer - 2] = (uint8_t)(processorState.programCounter & 0xFF);
    processorState.stackPointer -= 2;
    processorState.programCounter = (uint16_t)(exp ^ 0b11000111);
}

void rst_0() {
    rst(0);
}

void rst_1() {
    rst(1);
}

void rst_2() {
    rst(2);
}

void rst_3() {
    rst(3);
}

void rst_4() {
    rst(4);
}

void rst_5() {
    rst(5);
}

void rst_6() {
    rst(6);
}

void rst_7() {
    rst(7);
}

void ei() {
    processorState.intEnabled = true;
    ++processorState.programCounter;
}

void di() {
    processorState.intEnabled = false;
    ++processorState.programCounter;
}

void hlt() {
    ++processorState.programCounter;
    processorState.halted = true;
}

/////////////////////////////////////////// INPUT/OUTPUT ///////////////////////////////////////////

void in() {
    uint8_t devNumber = processorState.readOnlyMemory[processorState.programCounter + 1];
    processorState.A = processorState.deviceData[devNumber];
    processorState.programCounter += 2;
}

void out() {
    uint8_t devNumber = processorState.readOnlyMemory[processorState.programCounter + 1];
    processorState.deviceData[devNumber] = processorState.A;
    processorState.programCounter += 2;
}