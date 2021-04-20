#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

extern vector<vector<string>> interCode;
void generate_func(string type,string name);

void generate_end_func();

void generate_end_main();

void generate_para(string type,string name);

void generate_Const(string type,string name,string value);

void generate_Var(string type,string name,string value);

void generate_read(string name,string type);

void generate_print_str(string str);

void generate_cal(string result,string left,string op,string right,string leftType,string rightType);

void generate_print_var(vector<string> var, string type);

void generate_assign(string name,vector<string>info1,vector<string> info2,vector<string> right);

void generate_1array(string name, string type,int line);

void generate_1arrary_init(string name, string type, int position, string value);

void generate_2array(string name, string type, int line, int row);

void generate_2array_init(string name, string type, int line, int row, string value);

void generate_looper(string type,string beginlabel,string endlabel);

void generate_end_looper(string type, string beginlabel, string endlabel);

void generate_for_one(string name, vector<string> right);

void generate_for_three(string name1,string name2,string op,string step);

void generate_condition(vector<string> left,string op,vector<string> right);

void generate_switch(string type,vector<string>var);

void generate_case(string type, string value,string caselabel);

void generate_end_case(string casendlabel,string endlabel);

void generate_default();

void generate_end_default();

void generate_end_switch(string endlabel);

void generate_if(string elselabel,string endlabel);

void generate_end_ifpart(string elselabel, string endlabel);

void generate_else(string elselabel, string endlabel);

void generate_end_if_else(string elselabel, string endlabel);

void generate_end_if(string elselabel, string endlabel);

void generate_funcall(string name);

void generate_valueList(string name,vector<vector<string>> values);

void generate_ret(string type,vector<string> retvalue);

void generate_factor_funcall(string var);

void generate_load_array(string result,vector<string> arrayword);

void generate_j_main();

void outputcode();

