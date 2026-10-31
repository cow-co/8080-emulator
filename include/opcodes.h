#ifndef OPCODES_H
#define OPCODES_H
#include "emulator_state.h"

// We group here based on the type of opcode, not in order of opcode value
void nop(State* state);

void lxi_b(State* state);
void lxi_d(State* state);
void lxi_h(State* state);
void lxi_sp(State* state);

void mvi_b(State* state);
void mvi_c(State* state);
void mvi_d(State* state);
void mvi_e(State* state);
void mvi_h(State* state);
void mvi_l(State* state);
void mvi_a(State* state);
void mvi_m(State* state);

void mov_bc(State* state);
void mov_bd(State* state);
void mov_be(State* state);
void mov_bh(State* state);
void mov_bl(State* state);
void mov_bm(State* state);
void mov_ba(State* state);

void mov_cb(State* state);
void mov_cd(State* state);
void mov_ce(State* state);
void mov_ch(State* state);
void mov_cl(State* state);
void mov_cm(State* state);
void mov_ca(State* state);

void mov_db(State* state);
void mov_dc(State* state);
void mov_de(State* state);
void mov_dh(State* state);
void mov_dl(State* state);
void mov_dm(State* state);
void mov_da(State* state);

void mov_eb(State* state);
void mov_ec(State* state);
void mov_ed(State* state);
void mov_eh(State* state);
void mov_el(State* state);
void mov_em(State* state);
void mov_ea(State* state);

void mov_hb(State* state);
void mov_hc(State* state);
void mov_hd(State* state);
void mov_he(State* state);
void mov_hl(State* state);
void mov_hm(State* state);
void mov_ha(State* state);

void mov_lb(State* state);
void mov_lc(State* state);
void mov_ld(State* state);
void mov_le(State* state);
void mov_lh(State* state);
void mov_lm(State* state);
void mov_la(State* state);

void mov_mb(State* state);
void mov_mc(State* state);
void mov_md(State* state);
void mov_me(State* state);
void mov_mh(State* state);
void mov_ml(State* state);
void mov_ma(State* state);

void mov_ab(State* state);
void mov_ac(State* state);
void mov_ad(State* state);
void mov_ae(State* state);
void mov_ah(State* state);
void mov_al(State* state);
void mov_am(State* state);

void inr_b(State* state);
void inr_c(State* state);
void inr_d(State* state);
void inr_e(State* state);
void inr_h(State* state);
void inr_l(State* state);
void inr_a(State* state);
void inr_m(State* state);

void inx_b(State* state);
void inx_d(State* state);
void inx_h(State* state);
void inx_sp(State* state);

void dcr_b(State* state);
void dcr_c(State* state);
void dcr_d(State* state);
void dcr_e(State* state);
void dcr_h(State* state);
void dcr_l(State* state);
void dcr_a(State* state);
void dcr_m(State* state);

void dcx_b(State* state);
void dcx_d(State* state);
void dcx_h(State* state);
void dcx_sp(State* state);

void stax_b(State* state);
void stax_d(State* state);
void ldax_b(State* state);
void ldax_d(State* state);
void sphl(State* state);
void sta(State* state);
void lda(State* state);
void shld(State* state);
void lhld(State* state);

void xchg(State* state);
void xthl(State* state);

void pchl(State* state);
void jmp(State* state);
void jc(State* state);
void jnc(State* state);
void jz(State* state);
void jnz(State* state);
void jm(State* state);
void jp(State* state);
void jpe(State* state);
void jpo(State* state);

void push_b(State* state);
void push_d(State* state);
void push_h(State* state);
void push_psw(State* state);
void pop_b(State* state);
void pop_d(State* state);
void pop_h(State* state);
void pop_psw(State* state);

void rrc(State* state);
void rlc(State* state);
void rar(State* state);
void ral(State* state);

void cmc(State* state);
void stc(State* state);

void cma(State* state);
void daa(State* state);

void add_b(State* state);
void add_c(State* state);
void add_d(State* state);
void add_e(State* state);
void add_h(State* state);
void add_l(State* state);
void add_m(State* state);
void add_a(State* state);
void adc_b(State* state);
void adc_c(State* state);
void adc_d(State* state);
void adc_e(State* state);
void adc_h(State* state);
void adc_l(State* state);
void adc_m(State* state);
void adc_a(State* state);
void adi(State* state);
void aci(State* state);
void dad_b(State* state);
void dad_d(State* state);
void dad_h(State* state);
void dad_sp(State* state);

void sub_b(State* state);
void sub_c(State* state);
void sub_d(State* state);
void sub_e(State* state);
void sub_h(State* state);
void sub_l(State* state);
void sub_m(State* state);
void sub_a(State* state);

void sbb_b(State* state);
void sbb_c(State* state);
void sbb_d(State* state);
void sbb_e(State* state);
void sbb_h(State* state);
void sbb_l(State* state);
void sbb_m(State* state);
void sbb_a(State* state);

void sui(State* state);
void sbi(State* state);

void ana_b(State* state);
void ana_c(State* state);
void ana_d(State* state);
void ana_e(State* state);
void ana_h(State* state);
void ana_l(State* state);
void ana_m(State* state);
void ana_a(State* state);

void xra_b(State* state);
void xra_c(State* state);
void xra_d(State* state);
void xra_e(State* state);
void xra_h(State* state);
void xra_l(State* state);
void xra_m(State* state);
void xra_a(State* state);

void ora_b(State* state);
void ora_c(State* state);
void ora_d(State* state);
void ora_e(State* state);
void ora_h(State* state);
void ora_l(State* state);
void ora_m(State* state);
void ora_a(State* state);

void ani(State* state);
void ori(State* state);
void xri(State* state);

void cmp_b(State* state);
void cmp_c(State* state);
void cmp_d(State* state);
void cmp_e(State* state);
void cmp_h(State* state);
void cmp_l(State* state);
void cmp_m(State* state);
void cmp_a(State* state);
void cpi(State* state);

void call(State* state);
void cc(State* state);
void cnc(State* state);
void cp(State* state);
void cm(State* state);
void cz(State* state);
void cnz(State* state);
void cpe(State* state);
void cpo(State* state);

void ret(State* state);
void rc(State* state);
void rnc(State* state);
void rp(State* state);
void rm(State* state);
void rz(State* state);
void rnz(State* state);
void rpe(State* state);
void rpo(State* state);

void rst_0(State* state);
void rst_1(State* state);
void rst_2(State* state);
void rst_3(State* state);
void rst_4(State* state);
void rst_5(State* state);
void rst_6(State* state);
void rst_7(State* state);

void ei(State* state);
void di(State* state);
void hlt(State* state);

void in(State* state);
void out(State* state);

#endif