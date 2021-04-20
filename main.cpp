#include"getsym.h"
#include<iostream>
#include<vector>
#include<string>
#include"statement.h"
#include"mips.h"
using namespace std;
extern vector<vector<string>> composition;

int main() {
	lexical();
	//cout << composition.size();
	procedur();
	errorPut();
	//errorTest();
	outputcode();
	count_all_var();
	generate_mips();
	outputMips();
	return 0;
}