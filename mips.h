#pragma once
#include"intermediatecode.h"
#include<map>
void generate_mips();

void mips_const();

void mips_var();

void mips_cal();

void count_all_var();

void mips_lw(string name,string type);

void mips_read();

void mips_printstr();

void mips_printvar();

void mips_assign();

void outputMips();

void mips_func();

void mips_1array();

void mips_1array_init();

void mips_2array();

void mips_2array_init();

int getLocalPosition(string name);

void count_all_var();

int getFunSpace();

int getVarPosition(string name);

void mips_load_array();

void mips_if();

void mips_ifpart();

void mips_else();

void mips_endif();

void mips_endif_else();

void mips_for();

void mips_while();

void mips_end_while();

void mips_end_for();

void mips_switch();

void mips_case();

void mips_end_case();

void mips_end_switch();

void mips_valuelist();

void mips_funfactor();

void mips_ret();

void mips_fun_call();