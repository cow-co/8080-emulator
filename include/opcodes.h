#ifndef OPCODES_H
#define OPCODES_H

// We group here based on the type of opcode, not in order of opcode value
void nop();

void lxi_b();
void lxi_d();
void lxi_h();
void lxi_sp();

void inr_b();
void inr_c();
void inr_d();
void inr_e();
void inr_h();
void inr_l();
void inr_a();
void inr_m();

void inx_b();
void inx_d();
void inx_h();
void inx_sp();

void dcr_b();
void dcr_c();
void dcr_d();
void dcr_e();
void dcr_h();
void dcr_l();
void dcr_a();
void dcr_m();

void dcx_b();
void dcx_d();
void dcx_h();
void dcx_sp();

#endif