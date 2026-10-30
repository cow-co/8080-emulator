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

void stax_b();
void stax_d();
void ldax_b();
void ldax_d();
void sphl();
void sta();
void lda();
void shld();
void lhld();

void xchg();
void xthl();

void pchl();
void jmp();
void jc();
void jnc();
void jz();
void jnz();
void jm();
void jp();
void jpe();
void jpo();

void push_b();
void push_d();
void push_h();
void push_psw();
void pop_b();
void pop_d();
void pop_h();
void pop_psw();

void rrc();
void rlc();
void rar();
void ral();

void cmc();
void stc();

void cma();
void daa();

void add_b();
void add_c();
void add_d();
void add_e();
void add_h();
void add_l();
void add_m();
void add_a();
void adc_b();
void adc_c();
void adc_d();
void adc_e();
void adc_h();
void adc_l();
void adc_m();
void adc_a();
void adi();
void aci();
void dad_b();
void dad_d();
void dad_h();
void dad_sp();

void sub_b();
void sub_c();
void sub_d();
void sub_e();
void sub_h();
void sub_l();
void sub_m();
void sub_a();

void sbb_b();
void sbb_c();
void sbb_d();
void sbb_e();
void sbb_h();
void sbb_l();
void sbb_m();
void sbb_a();

void sui();
void sbi();

void ana_b();
void ana_c();
void ana_d();
void ana_e();
void ana_h();
void ana_l();
void ana_m();
void ana_a();

void xra_b();
void xra_c();
void xra_d();
void xra_e();
void xra_h();
void xra_l();
void xra_m();
void xra_a();

void ora_b();
void ora_c();
void ora_d();
void ora_e();
void ora_h();
void ora_l();
void ora_m();
void ora_a();

void ani();
void ori();
void xri();

void cmp_b();
void cmp_c();
void cmp_d();
void cmp_e();
void cmp_h();
void cmp_l();
void cmp_m();
void cmp_a();
void cpi();

void call();
void cc();
void cnc();
void cp();
void cm();
void cz();
void cnz();
void cpe();
void cpo();

void ret();
void rc();
void rnc();
void rp();
void rm();
void rz();
void rnz();
void rpe();
void rpo();

void rst_0();
void rst_1();
void rst_2();
void rst_3();
void rst_4();
void rst_5();
void rst_6();
void rst_7();

void ei();
void di();
void hlt();

void in();
void out();

#endif