#include "opcodes.h"
#include "state.h"

void nop() {
    processorState.programCounter += 1;
}

void lxi(uint8_t* const highRegister, uint8_t* const lowRegister) {
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

void inr(uint8_t* const reg) {
    *reg += 1;
    ++processorState.programCounter;
}

void inx(uint8_t* const highRegister, uint8_t* const lowRegister) {
    // TODO Implement
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

void inr_a() {
    inr(&processorState.A);
}

void inr_m() {
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

void dcr(uint8_t* const reg) {
    *reg -= 1;
    ++processorState.programCounter;
}

void dcx(uint8_t* const highRegister, uint8_t* const lowRegister) {
    // TODO Implement
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

void dcr_a() {
    dcr(&processorState.A);
}

void dcr_m() {
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