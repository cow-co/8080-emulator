#include "opcodes.h"
#include "state.h"

const uint16_t form_memory_ref() {
    uint16_t result = ((uint16_t)processorState.H) << 8;
    result |= (uint16_t)processorState.L;
    return result;
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
    const uint16_t addr = form_memory_ref();
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
    const uint16_t addr = form_memory_ref();
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
    const uint16_t addr = form_memory_ref();
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
    const uint16_t addr = form_memory_ref();
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
    const uint16_t addr = form_memory_ref();
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
    const uint16_t addr = form_memory_ref();
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
    const uint16_t addr = form_memory_ref();
    mov(&processorState.L, &processorState.readWriteMemory[addr]);
}
void mov_la() {
    mov(&processorState.L, &processorState.A);
}

void mov_mb() {
    const uint16_t addr = form_memory_ref();
    mov(&processorState.readWriteMemory[addr], &processorState.C);
}
void mov_mc() {
    const uint16_t addr = form_memory_ref();
    mov(&processorState.readWriteMemory[addr], &processorState.C);
}
void mov_md() {
    const uint16_t addr = form_memory_ref();
    mov(&processorState.readWriteMemory[addr], &processorState.D);
}
void mov_me() {
    const uint16_t addr = form_memory_ref();
    mov(&processorState.readWriteMemory[addr], &processorState.E);
}
void mov_mh() {
    const uint16_t addr = form_memory_ref();
    mov(&processorState.readWriteMemory[addr], &processorState.H);
}
void mov_ml() {
    const uint16_t addr = form_memory_ref();
    mov(&processorState.readWriteMemory[addr], &processorState.L);
}
void mov_ma() {
    const uint16_t addr = form_memory_ref();
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
    const uint16_t addr = form_memory_ref();
    mov(&processorState.A, &processorState.readWriteMemory[addr]);
}

/////////////////////////////////////////// INR ///////////////////////////////////////////

void inr(uint8_t* const dst) {
    *dst += 1;
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
    const uint16_t addr = form_memory_ref();
    inr(&processorState.readWriteMemory[addr]);
}

void inr_a() {
    inr(&processorState.A);
}

/////////////////////////////////////////// INX ///////////////////////////////////////////

void inx(uint8_t* const highRegister, uint8_t* const lowRegister) {
    // TODO Implement
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
    // TODO Implement
    ++processorState.programCounter;
}

/////////////////////////////////////////// DCR ///////////////////////////////////////////

void dcr(uint8_t* const reg) {
    *reg -= 1;
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
    const uint16_t addr = form_memory_ref();
    dcr(&processorState.readWriteMemory[addr]);
}

void dcr_a() {
    dcr(&processorState.A);
}

/////////////////////////////////////////// DCX ///////////////////////////////////////////

void dcx(uint8_t* const highRegister, uint8_t* const lowRegister) {
    // TODO Implement
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
    // TODO Implement
    ++processorState.programCounter;
}