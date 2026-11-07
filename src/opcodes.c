#include "opcodes.h"
#include "emulator_state.h"

uint16_t form_2_byte_from_1_bytes(const uint8_t highRegister, const uint8_t lowRegister) {
    uint16_t result = (uint16_t)highRegister << 8;
    result |= (uint16_t)lowRegister;
    return result;
}

void assign_parity(State* state, unsigned value, size_t size) {
    unsigned par = 0;
    value = (value & ((1 << size) - 1));
    for (size_t i = 0; i < size; ++i) {
        if (value & 0x01) {
            ++par;
        }
        value = value >> 1;
    }
    state->parity = !(par & 0x01);
}

uint8_t nop(State* state) {
    state->programCounter += 1;
    return 4;
}

/////////////////////////////////////////// LXI ///////////////////////////////////////////

uint8_t lxi(State* state, uint8_t* const highRegister, uint8_t* const lowRegister) {
    // Load extended immediate
    *highRegister = state->memory[state->programCounter + 2];
    *lowRegister = state->memory[state->programCounter + 1];
    state->programCounter += 3;
    return 10;
}

uint8_t lxi_b(State* state) {
    return lxi(state, &state->B, &state->C);
}

uint8_t lxi_d(State* state) {
    return lxi(state, &state->D, &state->E);
}

uint8_t lxi_h(State* state) {
    return lxi(state, &state->H, &state->L);
}

uint8_t lxi_sp(State* state) {
    state->stackPointer = ((uint16_t)state->memory[state->programCounter + 2]) << 8;
    state->stackPointer |= (uint16_t)state->memory[state->programCounter + 1];
    state->programCounter += 3;
    return 10;
}

/////////////////////////////////////////// MVI ///////////////////////////////////////////

void mvi(State* state, uint8_t* const dst) {
    // Move an immediate
    *dst = state->memory[state->programCounter + 1];
    state->programCounter += 2;
}

uint8_t mvi_b(State* state) {
    mvi(state, &state->B);
    return 7;
}

uint8_t mvi_c(State* state) {
    mvi(state, &state->C);
    return 7;
}

uint8_t mvi_d(State* state) {
    mvi(state, &state->D);
    return 7;
}

uint8_t mvi_e(State* state) {
    mvi(state, &state->E);
    return 7;
}

uint8_t mvi_h(State* state) {
    mvi(state, &state->H);
    return 7;
}

uint8_t mvi_l(State* state) {
    mvi(state, &state->L);
    return 7;
}

uint8_t mvi_a(State* state) {
    mvi(state, &state->A);
    return 7;
}

uint8_t mvi_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mvi(state, &state->memory[addr]);
    return 10;
}

/////////////////////////////////////////// MOV ///////////////////////////////////////////

void mov(State* state, uint8_t* const dst, uint8_t* const src) {
    *dst = *src;
    ++state->programCounter;
}

uint8_t mov_bc(State* state) {
    mov(state, &state->B, &state->C);
    return 5;
}
uint8_t mov_bd(State* state) {
    mov(state, &state->B, &state->D);
    return 5;
}
uint8_t mov_be(State* state) {
    mov(state, &state->B, &state->E);
    return 5;
}
uint8_t mov_bh(State* state) {
    mov(state, &state->B, &state->H);
    return 5;
}
uint8_t mov_bl(State* state) {
    mov(state, &state->B, &state->L);
    return 5;
}
uint8_t mov_bm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->B, &state->memory[addr]);
    return 7;
}
uint8_t mov_ba(State* state) {
    mov(state, &state->B, &state->A);
    return 5;
}

uint8_t mov_cb(State* state) {
    mov(state, &state->C, &state->B);
    return 5;
}
uint8_t mov_cd(State* state) {
    mov(state, &state->C, &state->D);
    return 5;
}
uint8_t mov_ce(State* state) {
    mov(state, &state->C, &state->E);
    return 5;
}
uint8_t mov_ch(State* state) {
    mov(state, &state->C, &state->H);
    return 5;
}
uint8_t mov_cl(State* state) {
    mov(state, &state->C, &state->L);
    return 5;
}
uint8_t mov_cm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->C, &state->memory[addr]);
    return 7;
}
uint8_t mov_ca(State* state) {
    mov(state, &state->C, &state->A);
    return 5;
}

uint8_t mov_db(State* state) {
    mov(state, &state->D, &state->B);
    return 5;
}
uint8_t mov_dc(State* state) {
    mov(state, &state->D, &state->C);
    return 5;
}
uint8_t mov_de(State* state) {
    mov(state, &state->D, &state->E);
    return 5;
}
uint8_t mov_dh(State* state) {
    mov(state, &state->D, &state->H);
    return 5;
}
uint8_t mov_dl(State* state) {
    mov(state, &state->D, &state->L);
    return 5;
}
uint8_t mov_dm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->D, &state->memory[addr]);
    return 7;
}
uint8_t mov_da(State* state) {
    mov(state, &state->D, &state->A);
    return 5;
}

uint8_t mov_eb(State* state) {
    mov(state, &state->E, &state->B);
    return 5;
}
uint8_t mov_ec(State* state) {
    mov(state, &state->E, &state->C);
    return 5;
}
uint8_t mov_ed(State* state) {
    mov(state, &state->E, &state->D);
    return 5;
}
uint8_t mov_eh(State* state) {
    mov(state, &state->E, &state->H);
    return 5;
}
uint8_t mov_el(State* state) {
    mov(state, &state->E, &state->L);
    return 5;
}
uint8_t mov_em(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->E, &state->memory[addr]);
    return 7;
}
uint8_t mov_ea(State* state) {
    mov(state, &state->E, &state->A);
    return 5;
}

uint8_t mov_hb(State* state) {
    mov(state, &state->H, &state->B);
    return 5;
}
uint8_t mov_hc(State* state) {
    mov(state, &state->H, &state->C);
    return 5;
}
uint8_t mov_hd(State* state) {
    mov(state, &state->H, &state->D);
    return 5;
}
uint8_t mov_he(State* state) {
    mov(state, &state->H, &state->E);
    return 5;
}
uint8_t mov_hl(State* state) {
    mov(state, &state->H, &state->L);
    return 5;
}
uint8_t mov_hm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->H, &state->memory[addr]);
    return 7;
}
uint8_t mov_ha(State* state) {
    mov(state, &state->H, &state->A);
    return 5;
}

uint8_t mov_lb(State* state) {
    mov(state, &state->L, &state->B);
    return 5;
}
uint8_t mov_lc(State* state) {
    mov(state, &state->L, &state->C);
    return 5;
}
uint8_t mov_ld(State* state) {
    mov(state, &state->L, &state->D);
    return 5;
}
uint8_t mov_le(State* state) {
    mov(state, &state->L, &state->E);
    return 5;
}
uint8_t mov_lh(State* state) {
    mov(state, &state->L, &state->H);
    return 5;
}
uint8_t mov_lm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->L, &state->memory[addr]);
    return 7;
}
uint8_t mov_la(State* state) {
    mov(state, &state->L, &state->A);
    return 5;
}

uint8_t mov_mb(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->memory[addr], &state->B);
    return 7;
}
uint8_t mov_mc(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->memory[addr], &state->C);
    return 7;
}
uint8_t mov_md(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->memory[addr], &state->D);
    return 7;
}
uint8_t mov_me(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->memory[addr], &state->E);
    return 7;
}
uint8_t mov_mh(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->memory[addr], &state->H);
    return 7;
}
uint8_t mov_ml(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->memory[addr], &state->L);
    return 7;
}
uint8_t mov_ma(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->memory[addr], &state->A);
    return 7;
}

uint8_t mov_ab(State* state) {
    mov(state, &state->A, &state->B);
    return 5;
}
uint8_t mov_ac(State* state) {
    mov(state, &state->A, &state->C);
    return 5;
}
uint8_t mov_ad(State* state) {
    mov(state, &state->A, &state->D);
    return 5;
}
uint8_t mov_ae(State* state) {
    mov(state, &state->A, &state->E);
    return 5;
}
uint8_t mov_ah(State* state) {
    mov(state, &state->A, &state->H);
    return 5;
}
uint8_t mov_al(State* state) {
    mov(state, &state->A, &state->L);
    return 5;
}
uint8_t mov_am(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->A, &state->memory[addr]);
    return 7;
}

uint8_t mov_nop(State* state) {
    return 5;
}

/////////////////////////////////////////// INR ///////////////////////////////////////////

void inr(State* state, uint8_t* const dst) {
    // TODO Assign aux carry
    uint16_t res = *dst + 1;
    state->carry = (res & 0b100000000);
    *dst += 1;
    state->zero = *dst == 0;
    assign_parity(state, *dst, 8);
    state->sign = *dst & 0b10000000;
    ++state->programCounter;
}

uint8_t inr_b(State* state) {
    inr(state, &state->B);
    return 5;
}

uint8_t inr_c(State* state) {
    inr(state, &state->C);
    return 5;
}

uint8_t inr_d(State* state) {
    inr(state, &state->D);
    return 5;
}

uint8_t inr_e(State* state) {
    inr(state, &state->E);
    return 5;
}

uint8_t inr_h(State* state) {
    inr(state, &state->H);
    return 5;
}

uint8_t inr_l(State* state) {
    inr(state, &state->L);
    return 5;
}

uint8_t inr_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    inr(state, &state->memory[addr]);
    return 10;
}

uint8_t inr_a(State* state) {
    inr(state, &state->A);
    return 5;
}

/////////////////////////////////////////// INX ///////////////////////////////////////////

uint8_t inx(State* state, uint8_t* const highRegister, uint8_t* const lowRegister) {
    *lowRegister += 1;
    if (*lowRegister == 0) {
        *highRegister += 1;
    }
    ++state->programCounter;
    return 5;
}

uint8_t inx_b(State* state) {
    return inx(state, &state->B, &state->C);
}

uint8_t inx_d(State* state) {
    return inx(state, &state->D, &state->E);
}

uint8_t inx_h(State* state) {
    return inx(state, &state->H, &state->L);
}

uint8_t inx_sp(State* state) {
    ++state->stackPointer;
    ++state->programCounter;
    return 5;
}

/////////////////////////////////////////// DCR ///////////////////////////////////////////

void dcr(State* state, uint8_t* const reg) {
    // TODO Assign aux carry
    uint16_t res = *reg - 1;
    state->carry = (res & 0b100000000);
    *reg -= 1;
    state->zero = *reg == 0;
    assign_parity(state, *reg, 8);
    state->sign = *reg & 0b10000000;
    ++state->programCounter;
}

uint8_t dcr_b(State* state) {
    dcr(state, &state->B);
    return 5;
}

uint8_t dcr_c(State* state) {
    dcr(state, &state->C);
    return 5;
}

uint8_t dcr_d(State* state) {
    dcr(state, &state->D);
    return 5;
}

uint8_t dcr_e(State* state) {
    dcr(state, &state->E);
    return 5;
}

uint8_t dcr_h(State* state) {
    dcr(state, &state->H);
    return 5;
}

uint8_t dcr_l(State* state) {
    dcr(state, &state->L);
    return 5;
}

uint8_t dcr_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    dcr(state, &state->memory[addr]);
    return 10;
}

uint8_t dcr_a(State* state) {
    dcr(state, &state->A);
    return 5;
}

/////////////////////////////////////////// DCX ///////////////////////////////////////////

uint8_t dcx(State* state, uint8_t* const highRegister, uint8_t* const lowRegister) {
    *lowRegister -= 1;
    if (*lowRegister == UINT8_MAX) {
        *highRegister -= 1;
    }
    ++state->programCounter;
    return 5;
}

uint8_t dcx_b(State* state) {
    return dcx(state, &state->B, &state->C);
}

uint8_t dcx_d(State* state) {
    return dcx(state, &state->D, &state->E);
}

uint8_t dcx_h(State* state) {
    return dcx(state, &state->H, &state->L);
}

uint8_t dcx_sp(State* state) {
    --state->stackPointer;
    ++state->programCounter;
    return 5;
}

/////////////////////////////////////// LOAD/STORE ////////////////////////////////////////

uint8_t stax_b(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->B, state->C);
    write_memory(state, addr, state->A);
    ++state->programCounter;
    return 7;
}

uint8_t stax_d(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->D, state->E);
    write_memory(state, addr, state->A);
    ++state->programCounter;
    return 7;
}

uint8_t ldax_b(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->B, state->C);
    state->A = state->memory[addr];
    ++state->programCounter;
    return 7;
}

uint8_t ldax_d(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->D, state->E);
    state->A = state->memory[addr];
    ++state->programCounter;
    return 7;
}

uint8_t sphl(State* state) {
    state->stackPointer = form_2_byte_from_1_bytes(state->H, state->L);
    ++state->programCounter;
    return 5;
}

uint8_t sta(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->memory[state->programCounter + 2],
        state->memory[state->programCounter + 1]
    );
    write_memory(state, addr, state->A);
    state->programCounter += 3;
    return 13;
}

uint8_t lda(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->memory[state->programCounter + 2],
        state->memory[state->programCounter + 1]
    );
    state->A = state->memory[addr];
    state->programCounter += 3;
    return 13;
}

uint8_t shld(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->memory[state->programCounter + 2],
        state->memory[state->programCounter + 1]
    );
    write_memory(state, addr, state->L);
    write_memory(state, addr + 1, state->H);
    state->programCounter += 3;
    return 16;
}

uint8_t lhld(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->memory[state->programCounter + 2],
        state->memory[state->programCounter + 1]
    );
    state->L = state->memory[addr];
    state->H = state->memory[addr + 1];
    state->programCounter += 3;
    return 16;
}

/////////////////////////////////////// EXCHANGE ///////////////////////////////////////

uint8_t xchg(State* state) {
    uint8_t tmp = state->D;
    state->D = state->H;
    state->H = tmp;
    tmp = state->E;
    state->E = state->L;
    state->L = tmp;
    ++state->programCounter;
    return 4;
}

uint8_t xthl(State* state) {
    uint8_t tmp = state->L;
    state->L = state->memory[state->stackPointer];
    write_memory(state, state->stackPointer, tmp);
    tmp = state->H;
    state->H = state->memory[state->stackPointer + 1];
    write_memory(state, state->stackPointer + 1, tmp);
    ++state->programCounter;
    return 18;
}

/////////////////////////////////////////// JUMP ///////////////////////////////////////////

uint8_t pchl(State* state) {
    // NOTE: We do not increment PC after this
    state->programCounter = form_2_byte_from_1_bytes(state->H, state->L);
    return 5;
}

uint8_t jmp(State* state) {
    // NOTE: We do not increment PC after this
    state->programCounter = form_2_byte_from_1_bytes(
        state->memory[state->programCounter + 2],
        state->memory[state->programCounter + 1]
    );
    return 10;
}

uint8_t jc(State* state) {
    if (state->carry) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

uint8_t jnc(State* state) {
    if (!state->carry) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

uint8_t jz(State* state) {
    if (state->zero) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

uint8_t jnz(State* state) {
    if (!state->zero) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

uint8_t jm(State* state) {
    if (state->sign) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

uint8_t jp(State* state) {
    if (!state->sign) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

uint8_t jpe(State* state) {
    if (state->parity) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

uint8_t jpo(State* state) {
    if (!state->parity) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
    return 10;
}

/////////////////////////////////////////// STACK ///////////////////////////////////////////

uint8_t push(State* state, const uint8_t highByte, const uint8_t lowByte) {
    write_memory(state, state->stackPointer - 1, highByte);
    write_memory(state, state->stackPointer - 2, lowByte);
    ++state->programCounter;
    state->stackPointer -= 2;
    return 11;
}

uint8_t push_b(State* state) {
    return push(state, state->B, state->C);
}

uint8_t push_d(State* state) {
    return push(state, state->D, state->E);
}
uint8_t push_h(State* state) {
    return push(state, state->H, state->L);
}

uint8_t push_psw(State* state) {
    return push(state, state->A, flags(state));
}

// FIXME PUSH AND POP PSW NOT WORKING
uint8_t pop(State* state, uint8_t* const highByte, uint8_t* const lowByte) {
    *lowByte = state->memory[state->stackPointer];
    *highByte = state->memory[state->stackPointer + 1];
    ++state->programCounter;
    state->stackPointer += 2;
    return 10;
}

uint8_t pop_b(State* state) {
    return pop(state, &state->B, &state->C);
}

uint8_t pop_d(State* state) {
    return pop(state, &state->D, &state->E);
}
uint8_t pop_h(State* state) {
    return pop(state, &state->H, &state->L);
}

uint8_t pop_psw(State* state) {
    state->A = state->memory[state->stackPointer + 1];
    const uint8_t flags = state->memory[state->stackPointer];
    state->carry = flags & (uint8_t)1;
    state->parity= flags & (uint8_t)4;
    state->auxCarry = flags & (uint8_t)16;
    state->zero = flags & (uint8_t)64;
    state->sign = flags & (uint8_t)128;
    ++state->programCounter;
    state->stackPointer += 2;
    return 10;
}

/////////////////////////////////////////// ROTATE ///////////////////////////////////////////

uint8_t rlc(State* state) {
    state->carry = state->A & (uint8_t)128;
    state->A = state->A << 1;
    state->A |= (uint8_t)state->carry;
    ++state->programCounter;
    return 4;
}

uint8_t rrc(State* state) {
    state->carry = state->A & (uint8_t)1;
    state->A = state->A >> 1;
    state->A |= ((uint8_t)state->carry << 7);
    ++state->programCounter;
    return 4;
}

uint8_t ral(State* state) {
    const bool tmp = state->carry;
    state->carry = state->A & (uint8_t)128;
    state->A = state->A << 1;
    state->A |= (uint8_t)tmp;
    ++state->programCounter;
    return 4;
}

uint8_t rar(State* state) {
    const bool tmp = state->carry;
    state->carry = state->A & (uint8_t)1;
    state->A = state->A >> 1;
    state->A |= ((uint8_t)tmp << 7);
    ++state->programCounter;
    return 4;
}

/////////////////////////////////////////// CARRY BIT ///////////////////////////////////////////

uint8_t cmc(State* state) {
    state->carry = !state->carry;
    ++state->programCounter;
    return 4;
}

uint8_t stc(State* state) {
    state->carry = true;
    ++state->programCounter;
    return 4;
}

/////////////////////////////////////////// ACCUMULATOR ///////////////////////////////////////////

uint8_t cma(State* state) {
    state->A = ~state->A;
    ++state->programCounter;
    return 4;
}

uint8_t daa(State* state) {
    // Decimal adjust accumulator: converts accumulator into two decimal digits
    const uint8_t lowNibble = state->A & 0b00001111;
    const bool lowNibbleGreaterThanNine = lowNibble > 9;
    if (state->auxCarry || lowNibbleGreaterThanNine) {
        // Checks if the addition will generate a carry out of bit 3
        uint16_t res = lowNibble + 0b0110;
        state->auxCarry = (res & 0b10000);
        res = state->A + 6;
        state->A += 6;  // 22
    }
    
    const uint8_t highNibble = state->A & 0b11110000;
    const bool highNibbleGreaterThanNine = (highNibble >> 4) > 9;
    if (state->carry || highNibbleGreaterThanNine) {    // true
        // Checks if the addition will generate a carry out of bit 7
        uint16_t res = (highNibble + 0b01100000);
        state->carry = (res & 0b100000000);
        state->A += 0b01100000;
    }
    ++state->programCounter;
    return 4;
}

/////////////////////////////////////////// ARITHMETIC ///////////////////////////////////////////

void add(State* state, const uint8_t value) {
    uint8_t lsn = state->A & 0x0F;
    uint8_t valLSN = value & 0x0F;
    state->auxCarry = lsn + valLSN > 0xF;

    uint16_t res = state->A + value;
    state->carry = (res & 0b100000000);

    state->A += value;

    state->zero = state->A == 0;
    assign_parity(state, state->A, 8);
    state->sign = state->A & 0b10000000;
    ++state->programCounter;
}

uint8_t add_b(State* state) {
    add(state, state->B);
    return 4;
}

uint8_t add_c(State* state) {
    add(state, state->C);
    return 4;
}

uint8_t add_d(State* state) {
    add(state, state->D);
    return 4;
}

uint8_t add_e(State* state) {
    add(state, state->E);
    return 4;
}

uint8_t add_h(State* state) {
    add(state, state->H);
    return 4;
}

uint8_t add_l(State* state) {
    add(state, state->L);
    return 4;
}

uint8_t add_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    add(state, state->memory[addr]);
    return 7;
}

uint8_t add_a(State* state) {
    add(state, state->A);
    return 4;
}

void adc(State* state, const uint8_t value) {
    uint8_t lsn = state->A & 0x0F;
    uint8_t valLSN = (value + 1) & 0x0F;
    state->auxCarry = lsn + valLSN > 0xF;

    uint16_t res = state->A + value + (uint16_t)state->carry;   // 0000000100010100
    state->A += value;
    state->A += state->carry;
    state->carry = (res & 0b100000000); // true
    state->zero = state->A == 0;
    assign_parity(state, state->A, 8);
    state->sign = state->A & 0b10000000;
    ++state->programCounter;
}

uint8_t adc_b(State* state) {
    adc(state, state->B);
    return 4;
}

uint8_t adc_c(State* state) {
    adc(state, state->C);
    return 4;
}

uint8_t adc_d(State* state) {
    adc(state, state->D);
    return 4;
}

uint8_t adc_e(State* state) {
    adc(state, state->E);
    return 4;
}

uint8_t adc_h(State* state) {
    adc(state, state->H);
    return 4;
}

uint8_t adc_l(State* state) {
    adc(state, state->L);
    return 4;
}

uint8_t adc_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    adc(state, state->memory[addr]);
    return 7;
}

uint8_t adc_a(State* state) {
    adc(state, state->A);
    return 4;
}

uint8_t adi(State* state) {
    const uint8_t data = state->memory[state->programCounter + 1];
    add(state, data);
    ++state->programCounter;    // add() already increments the counter, so we only need to move it along by 1 here
    return 7;
}

uint8_t aci(State* state) {
    // Technically there is a very slight unnecessary overhead from assigning the condition bits unnecessarily in the 
    // first call to add(), but we don't care about that.
    const uint8_t data = state->memory[state->programCounter + 1];
    adc(state, data);
    ++state->programCounter;    // adc() already increments the counter, so we only need to move it along by 1 here
    return 7;
}

uint8_t dad(State* state, const uint16_t value) {
    const uint16_t hl = form_2_byte_from_1_bytes(state->H, state->L);
    uint32_t resCarried = value + hl;
    uint16_t res = hl + value;
    state->H = res >> 8;
    state->L = res & 0x00FF;
    state->carry = resCarried & 0x10000;
    ++state->programCounter;
    return 10;
}

uint8_t dad_b(State* state) {
    return dad(state, form_2_byte_from_1_bytes(state->B, state->C));
}

uint8_t dad_d(State* state) {
    return dad(state, form_2_byte_from_1_bytes(state->D, state->E));
}

uint8_t dad_h(State* state) {
    return dad(state, form_2_byte_from_1_bytes(state->H, state->L));
}

uint8_t dad_sp(State* state) {
    return dad(state, state->stackPointer);
}

void sub(State* state, const uint8_t value) {
    const uint8_t twosComp = ~value + 1;
    add(state, twosComp);  // Handles the program counter increment
    state->carry = !state->carry;
}

uint8_t sub_b(State* state) {
    sub(state, state->B);
    return 4;
}

uint8_t sub_c(State* state) {
    sub(state, state->C);
    return 4;
}

uint8_t sub_d(State* state) {
    sub(state, state->D);
    return 4;
}

uint8_t sub_e(State* state) {
    sub(state, state->E);
    return 4;
}

uint8_t sub_h(State* state) {
    sub(state, state->H);
    return 4;
}

uint8_t sub_l(State* state) {
    sub(state, state->L);
    return 4;
}

uint8_t sub_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    sub(state, state->memory[addr]);
    return 7;
}

uint8_t sub_a(State* state) {
    sub(state, state->A);
    return 4;
}

void sbb(State* state, const uint8_t value) {
    sub(state, value + state->carry);
}

uint8_t sbb_b(State* state) {
    sbb(state, state->B);
    return 4;
}

uint8_t sbb_c(State* state) {
    sbb(state, state->C);
    return 4;
}

uint8_t sbb_d(State* state) {
    sbb(state, state->D);
    return 4;
}

uint8_t sbb_e(State* state) {
    sbb(state, state->E);
    return 4;
}

uint8_t sbb_h(State* state) {
    sbb(state, state->H);
    return 4;
}

uint8_t sbb_l(State* state) {
    sbb(state, state->L);
    return 4;
}

uint8_t sbb_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    sbb(state, state->memory[addr]);
    return 7;
}

uint8_t sbb_a(State* state) {
    sbb(state, state->A);
    return 4;
}

uint8_t sui(State* state) {
    const uint8_t data = state->memory[state->programCounter + 1];
    sub(state, data);
    ++state->programCounter;    // Need an extra increment (on top of the one sub() gives us)
    return 7;
}

uint8_t sbi(State* state) {
    const uint8_t data = state->memory[state->programCounter + 1];
    sbb(state, data);
    ++state->programCounter;    // Need an extra increment (on top of the one sub() gives us)
    return 7;
}


/////////////////////////////////////////// LOGIC ///////////////////////////////////////////

void ana(State* state, const uint8_t value) {
    state->A &= value;
    state->carry = false;
    state->auxCarry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    ++state->programCounter;
}

uint8_t ana_b(State* state) {
    ana(state, state->B);
    return 4;
}

uint8_t ana_c(State* state) {
    ana(state, state->C);
    return 4;
}

uint8_t ana_d(State* state) {
    ana(state, state->D);
    return 4;
}

uint8_t ana_e(State* state) {
    ana(state, state->E);
    return 4;
}

uint8_t ana_h(State* state) {
    ana(state, state->H);
    return 4;
}

uint8_t ana_l(State* state) {
    ana(state, state->L);
    return 4;
}

uint8_t ana_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    ana(state, state->memory[addr]);
    return 7;
}

uint8_t ana_a(State* state) {
    ana(state, state->A);
    return 4;
}

void xra(State* state, const uint8_t value) {
    state->A ^= value;
    state->carry = false;
    state->auxCarry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    ++state->programCounter;
}

uint8_t xra_b(State* state) {
    xra(state, state->B);
    return 4;
}

uint8_t xra_c(State* state) {
    xra(state, state->C);
    return 4;
}

uint8_t xra_d(State* state) {
    xra(state, state->D);
    return 4;
}

uint8_t xra_e(State* state) {
    xra(state, state->E);
    return 4;
}

uint8_t xra_h(State* state) {
    xra(state, state->H);
    return 4;
}

uint8_t xra_l(State* state) {
    xra(state, state->L);
    return 4;
}

uint8_t xra_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    xra(state, state->memory[addr]);
    return 7;
}

uint8_t xra_a(State* state) {
    xra(state, state->A);
    return 4;
}

void ora(State* state, const uint8_t value) {
    state->A |= value;
    state->carry = false;
    state->auxCarry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    ++state->programCounter;
}

uint8_t ora_b(State* state) {
    ora(state, state->B);
    return 4;
}

uint8_t ora_c(State* state) {
    ora(state, state->C);
    return 4;
}

uint8_t ora_d(State* state) {
    ora(state, state->D);
    return 4;
}

uint8_t ora_e(State* state) {
    ora(state, state->E);
    return 4;
}

uint8_t ora_h(State* state) {
    ora(state, state->H);
    return 4;
}

uint8_t ora_l(State* state) {
    ora(state, state->L);
    return 4;
}

uint8_t ora_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    ora(state, state->memory[addr]);
    return 7;
}

uint8_t ora_a(State* state) {
    ora(state, state->A);
    return 4;
}

uint8_t ani(State* state) {
    const uint8_t data = state->memory[state->programCounter + 1];
    state->A &= data;
    state->carry = false;
    state->auxCarry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    state->programCounter += 2;
    return 7;
}

uint8_t xri(State* state) {
    const uint8_t data = state->memory[state->programCounter + 1];
    state->A ^= data;
    state->carry = false;
    state->auxCarry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    state->programCounter += 2;
    return 7;
}

uint8_t ori(State* state) {
    const uint8_t data = state->memory[state->programCounter + 1];
    state->A |= data;
    state->carry = false;
    state->auxCarry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    state->programCounter += 2;
    return 7;
}

void cmp(State* state, const uint8_t value) {
    // Slightly different logic than sub (don't set accumulator) so let's keep this separate
    // (for now at least)
    const uint8_t twosComp = ~value + 1;    
    uint8_t lsn = state->A & 0x0F;
    uint8_t valLSN = twosComp & 0x0F;
    state->auxCarry = lsn + valLSN > 0xF;

    uint8_t res = state->A - value;
    state->carry = state->A < value;
    state->zero = (res == 0);
    assign_parity(state, res, 8);
    state->sign = res & 0b10000000;
    ++state->programCounter;
}

uint8_t cmp_b(State* state) {
    cmp(state, state->B);
    return 4;
}

uint8_t cmp_c(State* state) {
    cmp(state, state->C);
    return 4;
}

uint8_t cmp_d(State* state) {
    cmp(state, state->D);
    return 4;
}

uint8_t cmp_e(State* state) {
    cmp(state, state->E);
    return 4;
}

uint8_t cmp_h(State* state) {
    cmp(state, state->H);
    return 4;
}

uint8_t cmp_l(State* state) {
    cmp(state, state->L);
    return 4;
}

uint8_t cmp_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    cmp(state, state->memory[addr]);
    return 7;
}

uint8_t cmp_a(State* state) {
    cmp(state, state->A);
    return 4;
}

uint8_t cpi(State* state) {
    const uint8_t data = state->memory[state->programCounter + 1];
    cmp(state, data);
    ++state->programCounter;    // cmp() already increments this by one
    return 7;
}

/////////////////////////////////////////// CALL/RET ///////////////////////////////////////////


uint8_t call(State* state) {
    uint16_t callAddr = form_2_byte_from_1_bytes(
        state->memory[state->programCounter + 2],
        state->memory[state->programCounter + 1]
    );
#ifdef __CPUDIAG__
    if (callAddr == 5) {
        if (state->C == 9) {
            uint16_t offset = form_2_byte_from_1_bytes(
                state->D, state->E
            );
            char* str = &state->memory[offset + 3];
            while (*str != '$') {
                printf("%c", *str++);
            }
            printf("\n");
            exit(1);
        } else if (state->C == 2) {
            printf("Print char\n");
        }
    } else if (callAddr == 0) {
        exit(0);
    }
#endif
    uint16_t ret = state->programCounter + 3;
    write_memory(state, state->stackPointer - 1, (ret >> 8));
    write_memory(state, state->stackPointer - 2, (ret & 0xFF));
    state->stackPointer -= 2;
    state->programCounter = callAddr;
    return 17;
}

uint8_t cc(State* state) {
    if (state->carry) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t cnc(State* state) {
    if (!state->carry) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t cz(State* state) {
    if (state->zero) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t cnz(State* state) {
    if (!state->zero) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t cm(State* state) {
    if (state->sign) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t cp(State* state) {
    if (!state->sign) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t cpe(State* state) {
    if (state->parity) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t cpo(State* state) {
    if (!state->parity) {
        return call(state);
    } else {
        state->programCounter += 3;
        return 11;
    }
}

uint8_t ret(State* state) {
    // NOTE We rely on zero-extension of unsigned values here.
    state->programCounter = (state->memory[state->stackPointer + 1] << 8);  // This sets the high byte (and sets low byte to 0, via 0-extension)
    state->programCounter |= state->memory[state->stackPointer + 0];        // This sets the low byte
    state->stackPointer += 2;
    return 10;
}

uint8_t rc(State* state) {
    if (state->carry) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

uint8_t rnc(State* state) {
    if (!state->carry) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

uint8_t rz(State* state) {
    if (state->zero) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

uint8_t rnz(State* state) {
    if (!state->zero) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

uint8_t rm(State* state) {
    if (state->sign) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

uint8_t rp(State* state) {
    if (!state->sign) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

uint8_t rpe(State* state) {
    if (state->parity) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

uint8_t rpo(State* state) {
    if (!state->parity) {
        ret(state);
        return 11;
    } else {
        ++state->programCounter;
        return 5;
    }
}

/////////////////////////////////////////// INTERRUPTS/RESTARTS ///////////////////////////////////////////

uint8_t rst(State* state, const uint8_t exp) {
    write_memory(state, state->stackPointer - 1, (state->programCounter >> 8));
    write_memory(state, state->stackPointer - 2, (state->programCounter & 0xFF));
    state->stackPointer -= 2;
    state->programCounter = (uint16_t)(exp ^ 0b11000111);
    return 11;
}

uint8_t rst_0(State* state) {
    return rst(state, 0);
}

uint8_t rst_1(State* state) {
    return rst(state, 1);
}

uint8_t rst_2(State* state) {
    return rst(state, 2);
}

uint8_t rst_3(State* state) {
    return rst(state, 3);
}

uint8_t rst_4(State* state) {
    return rst(state, 4);
}

uint8_t rst_5(State* state) {
    return rst(state, 5);
}

uint8_t rst_6(State* state) {
    return rst(state, 6);
}

uint8_t rst_7(State* state) {
    return rst(state, 7);
}

uint8_t ei(State* state) {
    state->intEnabled = true;
    ++state->programCounter;
    return 4;
}

uint8_t di(State* state) {
    state->intEnabled = false;
    ++state->programCounter;
    return 4;
}

uint8_t hlt(State* state) {
    ++state->programCounter;
    state->halted = true;
    return 7;
}

/////////////////////////////////////////// INPUT/OUTPUT ///////////////////////////////////////////

uint8_t in(State* state) {
    uint8_t devNumber = state->memory[state->programCounter + 1];
    state->A = state->inputData[devNumber];
    state->programCounter += 2;
    return 10;
}

uint8_t out(State* state) {
    uint8_t devNumber = state->memory[state->programCounter + 1];
    state->outputData[devNumber] = state->A;
    state->programCounter += 2;
    return 10;
}