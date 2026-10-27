#ifndef OPCODES_H
#define OPCODES_H

// We group here based on the type of opcode, not in order of opcode value
void nop();

void lxi_b();
void lxi_d();
void lxi_h();
void lxi_sp();

void mvi_b();
void mvi_c();
void mvi_d();
void mvi_e();
void mvi_h();
void mvi_l();
void mvi_a();
void mvi_m();

void mov_bc();
void mov_bd();
void mov_be();
void mov_bh();
void mov_bl();
void mov_bm();
void mov_ba();

void mov_cb();
void mov_cd();
void mov_ce();
void mov_ch();
void mov_cl();
void mov_cm();
void mov_ca();

void mov_db();
void mov_dc();
void mov_de();
void mov_dh();
void mov_dl();
void mov_dm();
void mov_da();

void mov_eb();
void mov_ec();
void mov_ed();
void mov_eh();
void mov_el();
void mov_em();
void mov_ea();

void mov_hb();
void mov_hc();
void mov_hd();
void mov_he();
void mov_hl();
void mov_hm();
void mov_ha();

void mov_lb();
void mov_lc();
void mov_ld();
void mov_le();
void mov_lh();
void mov_lm();
void mov_la();

void mov_mb();
void mov_mc();
void mov_md();
void mov_me();
void mov_mh();
void mov_ml();
void mov_ma();

void mov_ab();
void mov_ac();
void mov_ad();
void mov_ae();
void mov_ah();
void mov_al();
void mov_am();

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