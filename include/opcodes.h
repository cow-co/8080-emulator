#ifndef OPCODES_H
#define OPCODES_H
#include "emulator_state.h"

// We group here based on the type of opcode, not in order of opcode value
uint8_t nop(State* state);

uint8_t lxi_b(State* state);
uint8_t lxi_d(State* state);
uint8_t lxi_h(State* state);
uint8_t lxi_sp(State* state);

uint8_t mvi_b(State* state);
uint8_t mvi_c(State* state);
uint8_t mvi_d(State* state);
uint8_t mvi_e(State* state);
uint8_t mvi_h(State* state);
uint8_t mvi_l(State* state);
uint8_t mvi_a(State* state);
uint8_t mvi_m(State* state);

uint8_t mov_bc(State* state);
uint8_t mov_bd(State* state);
uint8_t mov_be(State* state);
uint8_t mov_bh(State* state);
uint8_t mov_bl(State* state);
uint8_t mov_bm(State* state);
uint8_t mov_ba(State* state);

uint8_t mov_cb(State* state);
uint8_t mov_cd(State* state);
uint8_t mov_ce(State* state);
uint8_t mov_ch(State* state);
uint8_t mov_cl(State* state);
uint8_t mov_cm(State* state);
uint8_t mov_ca(State* state);

uint8_t mov_db(State* state);
uint8_t mov_dc(State* state);
uint8_t mov_de(State* state);
uint8_t mov_dh(State* state);
uint8_t mov_dl(State* state);
uint8_t mov_dm(State* state);
uint8_t mov_da(State* state);

uint8_t mov_eb(State* state);
uint8_t mov_ec(State* state);
uint8_t mov_ed(State* state);
uint8_t mov_eh(State* state);
uint8_t mov_el(State* state);
uint8_t mov_em(State* state);
uint8_t mov_ea(State* state);

uint8_t mov_hb(State* state);
uint8_t mov_hc(State* state);
uint8_t mov_hd(State* state);
uint8_t mov_he(State* state);
uint8_t mov_hl(State* state);
uint8_t mov_hm(State* state);
uint8_t mov_ha(State* state);

uint8_t mov_lb(State* state);
uint8_t mov_lc(State* state);
uint8_t mov_ld(State* state);
uint8_t mov_le(State* state);
uint8_t mov_lh(State* state);
uint8_t mov_lm(State* state);
uint8_t mov_la(State* state);

uint8_t mov_mb(State* state);
uint8_t mov_mc(State* state);
uint8_t mov_md(State* state);
uint8_t mov_me(State* state);
uint8_t mov_mh(State* state);
uint8_t mov_ml(State* state);
uint8_t mov_ma(State* state);

uint8_t mov_ab(State* state);
uint8_t mov_ac(State* state);
uint8_t mov_ad(State* state);
uint8_t mov_ae(State* state);
uint8_t mov_ah(State* state);
uint8_t mov_al(State* state);
uint8_t mov_am(State* state);

/**
 * This is a no-op but takes one cycle longer than the actual NOP
 */
uint8_t mov_nop(State* state);

uint8_t inr_b(State* state);
uint8_t inr_c(State* state);
uint8_t inr_d(State* state);
uint8_t inr_e(State* state);
uint8_t inr_h(State* state);
uint8_t inr_l(State* state);
uint8_t inr_a(State* state);
uint8_t inr_m(State* state);

uint8_t inx_b(State* state);
uint8_t inx_d(State* state);
uint8_t inx_h(State* state);
uint8_t inx_sp(State* state);

uint8_t dcr_b(State* state);
uint8_t dcr_c(State* state);
uint8_t dcr_d(State* state);
uint8_t dcr_e(State* state);
uint8_t dcr_h(State* state);
uint8_t dcr_l(State* state);
uint8_t dcr_a(State* state);
uint8_t dcr_m(State* state);

uint8_t dcx_b(State* state);
uint8_t dcx_d(State* state);
uint8_t dcx_h(State* state);
uint8_t dcx_sp(State* state);

uint8_t stax_b(State* state);
uint8_t stax_d(State* state);
uint8_t ldax_b(State* state);
uint8_t ldax_d(State* state);
uint8_t sphl(State* state);
uint8_t sta(State* state);
uint8_t lda(State* state);
uint8_t shld(State* state);
uint8_t lhld(State* state);

uint8_t xchg(State* state);
uint8_t xthl(State* state);

uint8_t pchl(State* state);
uint8_t jmp(State* state);
uint8_t jc(State* state);
uint8_t jnc(State* state);
uint8_t jz(State* state);
uint8_t jnz(State* state);
uint8_t jm(State* state);
uint8_t jp(State* state);
uint8_t jpe(State* state);
uint8_t jpo(State* state);

uint8_t push_b(State* state);
uint8_t push_d(State* state);
uint8_t push_h(State* state);
uint8_t push_psw(State* state);
uint8_t pop_b(State* state);
uint8_t pop_d(State* state);
uint8_t pop_h(State* state);
uint8_t pop_psw(State* state);

uint8_t rrc(State* state);
uint8_t rlc(State* state);
uint8_t rar(State* state);
uint8_t ral(State* state);

uint8_t cmc(State* state);
uint8_t stc(State* state);

uint8_t cma(State* state);
uint8_t daa(State* state);

uint8_t add_b(State* state);
uint8_t add_c(State* state);
uint8_t add_d(State* state);
uint8_t add_e(State* state);
uint8_t add_h(State* state);
uint8_t add_l(State* state);
uint8_t add_m(State* state);
uint8_t add_a(State* state);
uint8_t adc_b(State* state);
uint8_t adc_c(State* state);
uint8_t adc_d(State* state);
uint8_t adc_e(State* state);
uint8_t adc_h(State* state);
uint8_t adc_l(State* state);
uint8_t adc_m(State* state);
uint8_t adc_a(State* state);
uint8_t adi(State* state);
uint8_t aci(State* state);
uint8_t dad_b(State* state);
uint8_t dad_d(State* state);
uint8_t dad_h(State* state);
uint8_t dad_sp(State* state);

uint8_t sub_b(State* state);
uint8_t sub_c(State* state);
uint8_t sub_d(State* state);
uint8_t sub_e(State* state);
uint8_t sub_h(State* state);
uint8_t sub_l(State* state);
uint8_t sub_m(State* state);
uint8_t sub_a(State* state);

uint8_t sbb_b(State* state);
uint8_t sbb_c(State* state);
uint8_t sbb_d(State* state);
uint8_t sbb_e(State* state);
uint8_t sbb_h(State* state);
uint8_t sbb_l(State* state);
uint8_t sbb_m(State* state);
uint8_t sbb_a(State* state);

uint8_t sui(State* state);
uint8_t sbi(State* state);

uint8_t ana_b(State* state);
uint8_t ana_c(State* state);
uint8_t ana_d(State* state);
uint8_t ana_e(State* state);
uint8_t ana_h(State* state);
uint8_t ana_l(State* state);
uint8_t ana_m(State* state);
uint8_t ana_a(State* state);

uint8_t xra_b(State* state);
uint8_t xra_c(State* state);
uint8_t xra_d(State* state);
uint8_t xra_e(State* state);
uint8_t xra_h(State* state);
uint8_t xra_l(State* state);
uint8_t xra_m(State* state);
uint8_t xra_a(State* state);

uint8_t ora_b(State* state);
uint8_t ora_c(State* state);
uint8_t ora_d(State* state);
uint8_t ora_e(State* state);
uint8_t ora_h(State* state);
uint8_t ora_l(State* state);
uint8_t ora_m(State* state);
uint8_t ora_a(State* state);

uint8_t ani(State* state);
uint8_t ori(State* state);
uint8_t xri(State* state);

uint8_t cmp_b(State* state);
uint8_t cmp_c(State* state);
uint8_t cmp_d(State* state);
uint8_t cmp_e(State* state);
uint8_t cmp_h(State* state);
uint8_t cmp_l(State* state);
uint8_t cmp_m(State* state);
uint8_t cmp_a(State* state);
uint8_t cpi(State* state);

uint8_t call(State* state);
uint8_t cc(State* state);
uint8_t cnc(State* state);
uint8_t cp(State* state);
uint8_t cm(State* state);
uint8_t cz(State* state);
uint8_t cnz(State* state);
uint8_t cpe(State* state);
uint8_t cpo(State* state);

uint8_t ret(State* state);
uint8_t rc(State* state);
uint8_t rnc(State* state);
uint8_t rp(State* state);
uint8_t rm(State* state);
uint8_t rz(State* state);
uint8_t rnz(State* state);
uint8_t rpe(State* state);
uint8_t rpo(State* state);

uint8_t rst_0(State* state);
uint8_t rst_1(State* state);
uint8_t rst_2(State* state);
uint8_t rst_3(State* state);
uint8_t rst_4(State* state);
uint8_t rst_5(State* state);
uint8_t rst_6(State* state);
uint8_t rst_7(State* state);

uint8_t ei(State* state);
uint8_t di(State* state);
uint8_t hlt(State* state);

uint8_t in(State* state);
uint8_t out(State* state);

#endif