#include "opcodes.h"
#include "state.h"

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

void nop(State* state) {
    state->programCounter += 1;
}

/////////////////////////////////////////// LXI ///////////////////////////////////////////

void lxi(State* state, uint8_t* const highRegister, uint8_t* const lowRegister) {
    // Load extended immediate
    *highRegister = state->readWriteMemory[state->programCounter + 2];
    *lowRegister = state->readWriteMemory[state->programCounter + 1];
    state->programCounter += 3;
}

void lxi_b(State* state) {
    lxi(state, &state->B, &state->C);
}

void lxi_d(State* state) {
    lxi(state, &state->D, &state->E);
}

void lxi_h(State* state) {
    lxi(state, &state->H, &state->L);
}

void lxi_sp(State* state) {
    state->stackPointer = ((uint16_t)state->readWriteMemory[state->programCounter + 2]) << 8;
    state->stackPointer |= (uint16_t)state->readWriteMemory[state->programCounter + 1];
    state->programCounter += 3;
}

/////////////////////////////////////////// MVI ///////////////////////////////////////////

void mvi(State* state, uint8_t* const dst) {
    // Move an immediate
    *dst = state->readWriteMemory[state->programCounter + 1];
    state->programCounter += 2;
}

void mvi_b(State* state) {
    mvi(state, &state->B);
}

void mvi_c(State* state) {
    mvi(state, &state->C);
}

void mvi_d(State* state) {
    mvi(state, &state->D);
}

void mvi_e(State* state) {
    mvi(state, &state->E);
}

void mvi_h(State* state) {
    mvi(state, &state->H);
}

void mvi_l(State* state) {
    mvi(state, &state->L);
}

void mvi_a(State* state) {
    mvi(state, &state->A);
}

void mvi_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mvi(state, &state->readWriteMemory[addr]);
}

/////////////////////////////////////////// MOV ///////////////////////////////////////////

void mov(State* state, uint8_t* const dst, uint8_t* const src) {
    *dst = *src;
    ++state->programCounter;
}

void mov_bc(State* state) {
    mov(state, &state->B, &state->C);
}
void mov_bd(State* state) {
    mov(state, &state->B, &state->D);
}
void mov_be(State* state) {
    mov(state, &state->B, &state->E);
}
void mov_bh(State* state) {
    mov(state, &state->B, &state->H);
}
void mov_bl(State* state) {
    mov(state, &state->B, &state->L);
}
void mov_bm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->B, &state->readWriteMemory[addr]);
}
void mov_ba(State* state) {
    mov(state, &state->B, &state->A);
}

void mov_cb(State* state) {
    mov(state, &state->C, &state->B);
}
void mov_cd(State* state) {
    mov(state, &state->C, &state->D);
}
void mov_ce(State* state) {
    mov(state, &state->C, &state->E);
}
void mov_ch(State* state) {
    mov(state, &state->C, &state->H);
}
void mov_cl(State* state) {
    mov(state, &state->C, &state->L);
}
void mov_cm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->C, &state->readWriteMemory[addr]);
}
void mov_ca(State* state) {
    mov(state, &state->C, &state->A);
}

void mov_db(State* state) {
    mov(state, &state->D, &state->B);
}
void mov_dc(State* state) {
    mov(state, &state->D, &state->C);
}
void mov_de(State* state) {
    mov(state, &state->D, &state->E);
}
void mov_dh(State* state) {
    mov(state, &state->D, &state->H);
}
void mov_dl(State* state) {
    mov(state, &state->D, &state->L);
}
void mov_dm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->D, &state->readWriteMemory[addr]);
}
void mov_da(State* state) {
    mov(state, &state->D, &state->A);
}

void mov_eb(State* state) {
    mov(state, &state->E, &state->C);
}
void mov_ec(State* state) {
    mov(state, &state->E, &state->C);
}
void mov_ed(State* state) {
    mov(state, &state->E, &state->D);
}
void mov_eh(State* state) {
    mov(state, &state->E, &state->H);
}
void mov_el(State* state) {
    mov(state, &state->E, &state->L);
}
void mov_em(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->E, &state->readWriteMemory[addr]);
}
void mov_ea(State* state) {
    mov(state, &state->E, &state->A);
}

void mov_hb(State* state) {
    mov(state, &state->H, &state->C);
}
void mov_hc(State* state) {
    mov(state, &state->H, &state->C);
}
void mov_hd(State* state) {
    mov(state, &state->H, &state->D);
}
void mov_he(State* state) {
    mov(state, &state->H, &state->E);
}
void mov_hl(State* state) {
    mov(state, &state->H, &state->L);
}
void mov_hm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->H, &state->readWriteMemory[addr]);
}
void mov_ha(State* state) {
    mov(state, &state->H, &state->A);
}

void mov_lb(State* state) {
    mov(state, &state->L, &state->C);
}
void mov_lc(State* state) {
    mov(state, &state->L, &state->C);
}
void mov_ld(State* state) {
    mov(state, &state->L, &state->D);
}
void mov_le(State* state) {
    mov(state, &state->L, &state->E);
}
void mov_lh(State* state) {
    mov(state, &state->L, &state->H);
}
void mov_lm(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->L, &state->readWriteMemory[addr]);
}
void mov_la(State* state) {
    mov(state, &state->L, &state->A);
}

void mov_mb(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->readWriteMemory[addr], &state->C);
}
void mov_mc(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->readWriteMemory[addr], &state->C);
}
void mov_md(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->readWriteMemory[addr], &state->D);
}
void mov_me(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->readWriteMemory[addr], &state->E);
}
void mov_mh(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->readWriteMemory[addr], &state->H);
}
void mov_ml(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->readWriteMemory[addr], &state->L);
}
void mov_ma(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->readWriteMemory[addr], &state->A);
}

void mov_ab(State* state) {
    mov(state, &state->A, &state->C);
}
void mov_ac(State* state) {
    mov(state, &state->A, &state->C);
}
void mov_ad(State* state) {
    mov(state, &state->A, &state->D);
}
void mov_ae(State* state) {
    mov(state, &state->A, &state->E);
}
void mov_ah(State* state) {
    mov(state, &state->A, &state->H);
}
void mov_al(State* state) {
    mov(state, &state->A, &state->L);
}
void mov_am(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    mov(state, &state->A, &state->readWriteMemory[addr]);
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

void inr_b(State* state) {
    inr(state, &state->B);
}

void inr_c(State* state) {
    inr(state, &state->C);
}

void inr_d(State* state) {
    inr(state, &state->D);
}

void inr_e(State* state) {
    inr(state, &state->E);
}

void inr_h(State* state) {
    inr(state, &state->H);
}

void inr_l(State* state) {
    inr(state, &state->L);
}

void inr_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    inr(state, &state->readWriteMemory[addr]);
}

void inr_a(State* state) {
    inr(state, &state->A);
}

/////////////////////////////////////////// INX ///////////////////////////////////////////

void inx(State* state, uint8_t* const highRegister, uint8_t* const lowRegister) {
    *lowRegister += 1;
    if (*lowRegister == 0) {
        *highRegister += 1;
    }
    ++state->programCounter;
}

void inx_b(State* state) {
    inx(state, &state->B, &state->C);
}

void inx_d(State* state) {
    inx(state, &state->D, &state->E);
}

void inx_h(State* state) {
    inx(state, &state->H, &state->L);
}

void inx_sp(State* state) {
    ++state->stackPointer;
    ++state->programCounter;
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

void dcr_b(State* state) {
    dcr(state, &state->B);
}

void dcr_c(State* state) {
    dcr(state, &state->C);
}

void dcr_d(State* state) {
    dcr(state, &state->D);
}

void dcr_e(State* state) {
    dcr(state, &state->E);
}

void dcr_h(State* state) {
    dcr(state, &state->H);
}

void dcr_l(State* state) {
    dcr(state, &state->L);
}

void dcr_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    dcr(state, &state->readWriteMemory[addr]);
}

void dcr_a(State* state) {
    dcr(state, &state->A);
}

/////////////////////////////////////////// DCX ///////////////////////////////////////////

void dcx(State* state, uint8_t* const highRegister, uint8_t* const lowRegister) {
    *lowRegister -= 1;
    if (*lowRegister == UINT8_MAX) {
        *highRegister -= 1;
    }
    ++state->programCounter;
}

void dcx_b(State* state) {
    dcx(state, &state->B, &state->C);
}

void dcx_d(State* state) {
    dcx(state, &state->D, &state->E);
}

void dcx_h(State* state) {
    dcx(state, &state->H, &state->L);
}

void dcx_sp(State* state) {
    --state->stackPointer;
    ++state->programCounter;
}

/////////////////////////////////////// LOAD/STORE ////////////////////////////////////////

void stax_b(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->B, state->C);
    write_memory(addr, state->A);
    ++state->programCounter;
}

void stax_d(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->D, state->E);
    write_memory(addr, state->A);
    ++state->programCounter;
}

void ldax_b(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->B, state->C);
    state->A = state->readWriteMemory[addr];
    ++state->programCounter;
}

void ldax_d(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->D, state->E);
    state->A = state->readWriteMemory[addr];
    ++state->programCounter;
}

void sphl(State* state) {
    state->stackPointer = form_2_byte_from_1_bytes(state->H, state->L);
    ++state->programCounter;
}

void sta(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->readWriteMemory[state->programCounter + 2],
        state->readWriteMemory[state->programCounter + 1]
    );
    write_memory(addr, state->A);
    state->programCounter += 3;
}

void lda(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->readWriteMemory[state->programCounter + 2],
        state->readWriteMemory[state->programCounter + 1]
    );
    state->A = state->readWriteMemory[addr];
    state->programCounter += 3;
}

void shld(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->readWriteMemory[state->programCounter + 2],
        state->readWriteMemory[state->programCounter + 1]
    );
    write_memory(addr, state->L);
    write_memory(addr + 1, state->H);
    state->programCounter += 3;
}

void lhld(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(
        state->readWriteMemory[state->programCounter + 2],
        state->readWriteMemory[state->programCounter + 1]
    );
    state->L = state->readWriteMemory[addr];
    state->H = state->readWriteMemory[addr + 1];
    state->programCounter += 3;
}

/////////////////////////////////////// EXCHANGE ///////////////////////////////////////

void xchg(State* state) {
    uint8_t tmp = state->D;
    state->D = state->H;
    state->H = tmp;
    tmp = state->E;
    state->E = state->L;
    state->L = tmp;
    ++state->programCounter;
}

void xthl(State* state) {
    uint8_t tmp = state->L;
    state->L = state->readWriteMemory[state->stackPointer];
    write_memory(state->stackPointer, tmp);
    tmp = state->H;
    state->H = state->readWriteMemory[state->stackPointer + 1];
    write_memory(state->stackPointer + 1, tmp);
    ++state->programCounter;
}

/////////////////////////////////////////// JUMP ///////////////////////////////////////////

void pchl(State* state) {
    // NOTE: We do not increment PC after this
    state->programCounter = form_2_byte_from_1_bytes(state->H, state->L);
}

void jmp(State* state) {
    // NOTE: We do not increment PC after this
    state->programCounter = form_2_byte_from_1_bytes(
        state->readWriteMemory[state->programCounter + 2],
        state->readWriteMemory[state->programCounter + 1]
    );
}

void jc(State* state) {
    if (state->carry) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

void jnc(State* state) {
    if (!state->carry) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

void jz(State* state) {
    if (state->zero) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

void jnz(State* state) {
    if (!state->zero) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

void jm(State* state) {
    if (state->sign) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

void jp(State* state) {
    if (!state->sign) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

void jpe(State* state) {
    if (state->parity) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

void jpo(State* state) {
    if (!state->parity) {
        jmp(state);
    } else {
        state->programCounter += 3;
    }
}

/////////////////////////////////////////// STACK ///////////////////////////////////////////

void push(State* state, const uint8_t highByte, const uint8_t lowByte) {
    write_memory(state->stackPointer - 1, highByte);
    write_memory(state->stackPointer - 2, lowByte);
    ++state->programCounter;
    state->stackPointer -= 2;
}

void push_b(State* state) {
    push(state, state->B, state->C);
}

void push_d(State* state) {
    push(state, state->D, state->E);
}
void push_h(State* state) {
    push(state, state->H, state->L);
}

void push_psw(State* state) {
    push(state, state->A, flags());
}

void pop(State* state, uint8_t* const highByte, uint8_t* const lowByte) {
    *lowByte = state->readWriteMemory[state->stackPointer];
    *highByte = state->readWriteMemory[state->stackPointer + 1];
    ++state->programCounter;
    state->stackPointer += 2;
}

void pop_b(State* state) {
    pop(state, &state->B, &state->C);
}

void pop_d(State* state) {
    pop(state, &state->D, &state->E);
}
void pop_h(State* state) {
    pop(state, &state->H, &state->L);
}

void pop_psw(State* state) {
    state->A = state->readWriteMemory[state->stackPointer];
    const uint8_t flags = state->readWriteMemory[state->stackPointer + 1];
    state->carry = flags & (uint8_t)1;
    state->parity= flags & (uint8_t)4;
    state->auxCarry = flags & (uint8_t)16;
    state->zero = flags & (uint8_t)64;
    state->sign = flags & (uint8_t)128;
    ++state->programCounter;
    state->stackPointer += 2;
}

/////////////////////////////////////////// ROTATE ///////////////////////////////////////////

void rlc(State* state) {
    state->carry = state->A & (uint8_t)128;
    state->A = state->A << 1;
    state->A |= (uint8_t)state->carry;
    ++state->programCounter;
}

void rrc(State* state) {
    state->carry = state->A & (uint8_t)1;
    state->A = state->A >> 1;
    state->A |= ((uint8_t)state->carry << 7);
    ++state->programCounter;
}

void ral(State* state) {
    const bool tmp = state->carry;
    state->carry = state->A & (uint8_t)128;
    state->A = state->A << 1;
    state->A |= (uint8_t)tmp;
    ++state->programCounter;
}

void rar(State* state) {
    const bool tmp = state->carry;
    state->carry = state->A & (uint8_t)1;
    state->A = state->A >> 1;
    state->A |= ((uint8_t)tmp << 7);
    ++state->programCounter;
}

/////////////////////////////////////////// CARRY BIT ///////////////////////////////////////////

void cmc(State* state) {
    state->carry = !state->carry;
    ++state->programCounter;
}

void stc(State* state) {
    state->carry = true;
    ++state->programCounter;
}

/////////////////////////////////////////// ACCUMULATOR ///////////////////////////////////////////

void cma(State* state) {
    state->A = ~state->A;
    ++state->programCounter;
}

void daa(State* state) {
    // Decimal adjust accumulator: converts accumulator into two decimal digits
    const uint8_t lowNibble = state->A & 0b00001111;
    const bool lowNibbleGreaterThanNine = lowNibble > 9;
    if (state->auxCarry || lowNibbleGreaterThanNine) {
        // Checks if the addition will generate a carry out of bit 3
        uint16_t res = lowNibble + 0b0110;
        state->auxCarry = (res & 0b10000);
        res = state->A + 6;
        state->carry = (res & 0b100000000);
        state->A += 6;
    }
    
    const uint8_t highNibble = state->A & 0b11110000;
    const bool highNibbleGreaterThanNine = (highNibble >> 4) > 9;
    if (state->carry || highNibbleGreaterThanNine) {
        // Checks if the addition will generate a carry out of bit 7
        uint16_t res = (highNibble + 0b01100000);
        state->carry = (res & 0b100000000);
        state->A += 0b01100000;
    }
    ++state->programCounter;
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

void add_b(State* state) {
    add(state, state->B);
}

void add_c(State* state) {
    add(state, state->C);
}

void add_d(State* state) {
    add(state, state->D);
}

void add_e(State* state) {
    add(state, state->E);
}

void add_h(State* state) {
    add(state, state->H);
}

void add_l(State* state) {
    add(state, state->L);
}

void add_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    add(state, state->readWriteMemory[addr]);
}

void add_a(State* state) {
    add(state, state->A);
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

void adc_b(State* state) {
    adc(state, state->B);
}

void adc_c(State* state) {
    adc(state, state->C);
}

void adc_d(State* state) {
    adc(state, state->D);
}

void adc_e(State* state) {
    adc(state, state->E);
}

void adc_h(State* state) {
    adc(state, state->H);
}

void adc_l(State* state) {
    adc(state, state->L);
}

void adc_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    adc(state, state->readWriteMemory[addr]);
}

void adc_a(State* state) {
    adc(state, state->A);
}

void adi(State* state) {
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    add(state, data);
    ++state->programCounter;    // add() already increments the counter, so we only need to move it along by 1 here
}

void aci(State* state) {
    // Technically there is a very slight unnecessary overhead from assigning the condition bits unnecessarily in the 
    // first call to add(), but we don't care about that.
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    adc(state, data);
    ++state->programCounter;    // adc() already increments the counter, so we only need to move it along by 1 here
}

void dad(State* state, const uint16_t value) {
    const uint16_t hl = form_2_byte_from_1_bytes(state->H, state->L);
    uint32_t resCarried = value + hl;
    uint16_t res = hl + value;
    state->H = res >> 8;
    state->L = res & 0x00FF;
    state->carry = resCarried & 0x10000;
    ++state->programCounter;
}

void dad_b(State* state) {
    dad(state, form_2_byte_from_1_bytes(state->B, state->C));
}

void dad_d(State* state) {
    dad(state, form_2_byte_from_1_bytes(state->D, state->E));

}

void dad_h(State* state) {
    dad(state, form_2_byte_from_1_bytes(state->H, state->L));

}

void dad_sp(State* state) {
    dad(state, state->stackPointer);
}

void sub(State* state, const uint8_t value) {
    const uint8_t twosComp = ~value + 1;
    add(state, twosComp);  // Handles the program counter increment
    state->carry = !state->carry;
}

void sub_b(State* state) {
    sub(state, state->B);
}

void sub_c(State* state) {
    sub(state, state->C);
}

void sub_d(State* state) {
    sub(state, state->D);
}

void sub_e(State* state) {
    sub(state, state->E);
}

void sub_h(State* state) {
    sub(state, state->H);
}

void sub_l(State* state) {
    sub(state, state->L);
}

void sub_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    sub(state, state->readWriteMemory[addr]);
}

void sub_a(State* state) {
    sub(state, state->A);
}

void sbb(State* state, const uint8_t value) {
    sub(state, value + state->carry);
}

void sbb_b(State* state) {
    sbb(state, state->B);
}

void sbb_c(State* state) {
    sbb(state, state->C);
}

void sbb_d(State* state) {
    sbb(state, state->D);
}

void sbb_e(State* state) {
    sbb(state, state->E);
}

void sbb_h(State* state) {
    sbb(state, state->H);
}

void sbb_l(State* state) {
    sbb(state, state->L);
}

void sbb_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    sbb(state, state->readWriteMemory[addr]);
}

void sbb_a(State* state) {
    sbb(state, state->A);
}

void sui(State* state) {
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    sub(state, data);
    ++state->programCounter;    // Need an extra increment (on top of the one sub() gives us)
}

void sbi(State* state) {
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    sbb(state, data);
    ++state->programCounter;    // Need an extra increment (on top of the one sub() gives us)
}


/////////////////////////////////////////// LOGIC ///////////////////////////////////////////

void ana(State* state, const uint8_t value) {
    state->A &= value;
    state->carry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    ++state->programCounter;
}

void ana_b(State* state) {
    ana(state, state->B);
}

void ana_c(State* state) {
    ana(state, state->C);
}

void ana_d(State* state) {
    ana(state, state->D);
}

void ana_e(State* state) {
    ana(state, state->E);
}

void ana_h(State* state) {
    ana(state, state->H);
}

void ana_l(State* state) {
    ana(state, state->L);
}

void ana_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    ana(state, state->readWriteMemory[addr]);
}

void ana_a(State* state) {
    ana(state, state->A);
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

void xra_b(State* state) {
    xra(state, state->B);
}

void xra_c(State* state) {
    xra(state, state->C);
}

void xra_d(State* state) {
    xra(state, state->D);
}

void xra_e(State* state) {
    xra(state, state->E);
}

void xra_h(State* state) {
    xra(state, state->H);
}

void xra_l(State* state) {
    xra(state, state->L);
}

void xra_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    xra(state, state->readWriteMemory[addr]);
}

void xra_a(State* state) {
    xra(state, state->A);
}

void ora(State* state, const uint8_t value) {
    state->A |= value;
    state->carry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    ++state->programCounter;
}

void ora_b(State* state) {
    ora(state, state->B);
}

void ora_c(State* state) {
    ora(state, state->C);
}

void ora_d(State* state) {
    ora(state, state->D);
}

void ora_e(State* state) {
    ora(state, state->E);
}

void ora_h(State* state) {
    ora(state, state->H);
}

void ora_l(State* state) {
    ora(state, state->L);
}

void ora_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    ora(state, state->readWriteMemory[addr]);
}

void ora_a(State* state) {
    ora(state, state->A);
}

void ani(State* state) {
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    state->A &= data;
    state->carry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    state->programCounter += 2;
}

void xri(State* state) {
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    state->A ^= data;
    state->carry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    state->programCounter += 2;
}

void ori(State* state) {
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    state->A |= data;
    state->carry = false;
    assign_parity(state, state->A, 8);
    state->zero = !state->A;
    state->sign = state->A & 0b10000000;
    state->programCounter += 2;
}

void cmp(State* state, const uint8_t value) {
    // Slightly different logic than sub (don't set accumulator) so let's keep this separate
    // (for now at least)
    const uint8_t twosComp = ~value + 1;
    
    uint8_t lsn = state->A & 0x0F;
    uint8_t valLSN = twosComp & 0x0F;
    state->auxCarry = lsn + valLSN > 0xF;

    uint16_t resWithCarry = state->A + twosComp;
    uint8_t res = state->A + twosComp;
    state->carry = !(resWithCarry & 0b100000000);

    state->zero = res== 0;
    assign_parity(state, res, 8);
    state->sign = res & 0b10000000;
    ++state->programCounter;
}

void cmp_b(State* state) {
    cmp(state, state->B);
}

void cmp_c(State* state) {
    cmp(state, state->C);
}

void cmp_d(State* state) {
    cmp(state, state->D);
}

void cmp_e(State* state) {
    cmp(state, state->E);
}

void cmp_h(State* state) {
    cmp(state, state->H);
}

void cmp_l(State* state) {
    cmp(state, state->L);
}

void cmp_m(State* state) {
    const uint16_t addr = form_2_byte_from_1_bytes(state->H, state->L);
    cmp(state, state->readWriteMemory[addr]);
}

void cmp_a(State* state) {
    cmp(state, state->A);
}

void cpi(State* state) {
    const uint8_t data = state->readWriteMemory[state->programCounter + 1];
    cmp(state, data);
}

/////////////////////////////////////////// CALL/RET ///////////////////////////////////////////

void call(State* state) {
    write_memory(state->stackPointer - 1, (state->programCounter >> 8));
    write_memory(state->stackPointer - 2, (state->programCounter & 0xFF));
    state->stackPointer -= 2;
    state->programCounter = form_2_byte_from_1_bytes(
        state->readWriteMemory[state->programCounter + 2],
        state->readWriteMemory[state->programCounter + 1]
    );
}

void cc(State* state) {
    if (state->carry) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void cnc(State* state) {
    if (!state->carry) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void cz(State* state) {
    if (state->zero) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void cnz(State* state) {
    if (!state->zero) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void cm(State* state) {
    if (state->sign) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void cp(State* state) {
    if (!state->sign) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void cpe(State* state) {
    if (state->parity) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void cpo(State* state) {
    if (!state->parity) {
        call(state);
    } else {
        state->programCounter += 3;
    }
}

void ret(State* state) {
    state->programCounter &= (state->readWriteMemory[state->stackPointer + 1] << 8);
    state->programCounter &= state->readWriteMemory[state->stackPointer + 0];
}

void rc(State* state) {
    if (state->carry) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

void rnc(State* state) {
    if (!state->carry) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

void rz(State* state) {
    if (state->zero) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

void rnz(State* state) {
    if (!state->zero) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

void rm(State* state) {
    if (state->sign) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

void rp(State* state) {
    if (!state->sign) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

void rpe(State* state) {
    if (state->parity) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

void rpo(State* state) {
    if (!state->parity) {
        ret(state);
    } else {
        state->programCounter += 3;
    }
}

/////////////////////////////////////////// INTERRUPTS/RESTARTS ///////////////////////////////////////////

void rst(State* state, const uint8_t exp) {
    write_memory(state->stackPointer - 1, (state->programCounter >> 8));
    write_memory(state->stackPointer - 2, (state->programCounter & 0xFF));
    state->stackPointer -= 2;
    state->programCounter = (uint16_t)(exp ^ 0b11000111);
}

void rst_0(State* state) {
    rst(state, 0);
}

void rst_1(State* state) {
    rst(state, 1);
}

void rst_2(State* state) {
    rst(state, 2);
}

void rst_3(State* state) {
    rst(state, 3);
}

void rst_4(State* state) {
    rst(state, 4);
}

void rst_5(State* state) {
    rst(state, 5);
}

void rst_6(State* state) {
    rst(state, 6);
}

void rst_7(State* state) {
    rst(state, 7);
}

void ei(State* state) {
    state->intEnabled = true;
    ++state->programCounter;
}

void di(State* state) {
    state->intEnabled = false;
    ++state->programCounter;
}

void hlt(State* state) {
    ++state->programCounter;
    state->halted = true;
}

/////////////////////////////////////////// INPUT/OUTPUT ///////////////////////////////////////////

void in(State* state) {
    uint8_t devNumber = state->readWriteMemory[state->programCounter + 1];
    state->A = state->deviceData[devNumber];
    state->programCounter += 2;
}

void out(State* state) {
    uint8_t devNumber = state->readWriteMemory[state->programCounter + 1];
    state->deviceData[devNumber] = state->A;
    state->programCounter += 2;
}