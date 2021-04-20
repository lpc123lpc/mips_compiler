#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include"statement.h"
#include"intermediatecode.h"
#include <regex>

using namespace std;

//ofstream out("C:\\Users\\lpc\\Desktop\\output.txt");
int position = 0;
int ifReturn=0;
int funposition = 0;
string funType = "";
extern vector<vector<string>> composition;
//0:number 1:string 2:type
extern ofstream error;
vector<string> refunction;
vector<string> voidfunction;
vector<vector<string>> signary;
int factorCount = 0;
int ifcount = 0;
int whilecount = 0;
int forcount = 0;
int switchcount = 0;
int casecount;
vector<vector<string>> varStack;
extern vector<vector<string>> errorList;
//0:linenum 1:const or var or array  2:type  3: name
bool nameDupError(string name) {
	for (int i = funposition; i < signary.size(); i++) {
		if (signary[i][3] == name) {
			return true;
		}
	}
	return false;
}

void insertError(string linenum,string type) {
	vector<string> temp;
	temp.push_back(linenum);
	temp.push_back(type);
	errorList.push_back(temp);
}

int getName(string s,string linenum) {
	std::transform(s.begin(),s.end(),s.begin(), ::tolower);
	for (int i = signary.size()-1; i >=0; i--) {
		if (signary[i][3] == s) {
			return i;
		}
	}
	insertError(linenum, "c");
	//error << linenum << " c\n";
	return -1;
}

int callName() {
	string name = composition[position][1];
	string linenum = composition[position][3];
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	int x = getName(name, linenum);
	return x;
}
void procedur() {
	if (composition[position][0] == "5") {
		constState();
	}
	if ((composition[position][0] == "6" || composition[position][0] == "7")
		&& composition[position + 1][0] == "1" && composition[position + 2][0] != "34") {
		varState();
	}
	generate_j_main();
	while ((composition[position][0] == "6" || composition[position][0] == "7") ||
		(composition[position][0] == "8" && composition[position+1][0] != "9")) {
		if (composition[position][0] == "6" || composition[position][0] == "7") {
			func();
		}
		else {
			voidfunc();
		}
	}
	mainFunc();
	//out << "<����>\n";
}

void constState() {//����˵��
	
	while (composition[position][0] == "5") {//��俪ͷconst
		string linenum = composition[position][3];
		output();
		position++;
		constDef();
		if (composition[position][0] == "32") {
			output();//����ֺ�
			position++;
		}
		else {
			insertError(linenum, "k");
			//error << linenum << " k\n";
		}
	}
	//out << "<����˵��>\n";
}

void constDef() {//��������
	//int or char
	string name;
	
	if (composition[position][0] == "6") {
		output();//output int
		position++;//IDENFR
		while (1) {
			if (composition[position][0] == "1") {
				name = composition[position][1];
				std::transform(name.begin(), name.end(), name.begin(), ::tolower);
				
				if (nameDupError(name)) {
					insertError(composition[position][3], "b");
					//error << composition[position][3] << " b\n";
				}
				else {
					vector<string> temp;
					temp.push_back(composition[position][3]);
					temp.push_back("const");
					temp.push_back("int");
					temp.push_back(name);
					signary.push_back(temp);
				}
				output();//output int
				position++;// =
				if (composition[position][0] == "31") {
					output();//otuput =
					position++;
					string temp = intDef();
					generate_Const("int", name, temp);
					if (composition[position][0] != "33") {
						//out << "<��������>\n";
						break;
					}
					else {
						output();
						position++;
					}
				}
			}
		}
	}
	else if (composition[position][0] == "7"){
		output();//output char
		position++;//IDENFR
		while (1) {
			if (composition[position][0] == "1") {
				name = composition[position][1];
				std::transform(name.begin(), name.end(), name.begin(), ::tolower);

				if (nameDupError(name)) {
					insertError(composition[position][3], "b");
					//error << composition[position][3] << " b\n";
				}
				else {
					vector<string> temp;
					temp.push_back(composition[position][3]);
					temp.push_back("const");
					temp.push_back("char");
					temp.push_back(name);
					signary.push_back(temp);
				}
				output();//IDENFR
				position++;// =
				if (composition[position][0] == "31") {
					output();//output =
					position++;
					generate_Const("char", name,"\'" +composition[position][1]+"\'");
					charDef();
					if (composition[position][0] != "33") {
						//out << "<��������>\n";
						break;
					}
					else {
						output();
						position++;
					}
				}
			}
		}
	}

}

void charDef() {
	if (composition[position][0] == "3") {
		output();//output charConst
		position++;
	}
}

string intDef() {//����
	string x;
	if (composition[position][0] == "20" || composition[position][0] == "21") {
		output();//output + or -
		position++;
		x = composition[position - 1][1] + composition[position][1];
		unIntDef();
		//out << "<����>\n";
	}
	else {
		x = composition[position][1];
		unIntDef();
		//out << "<����>\n";
	}
	return x;
}

void unIntDef() {//�޷�������
	if (composition[position][0] == "2") {
		output();//otuput unsigned int
		//out << "<�޷�������>\n";
		position++;
	
	}
	else {
		//error;

	}
}

void varState() {//����˵��
	while ((composition[position][0] == "6" || composition[position][0] == "7")
		   && composition[position+1][0] == "1" && composition[position + 2][0] != "34"){
		string linenum = composition[position][3];
		varDef();//
		if (composition[position][0] == "32") {
			output();//output ;
			position++;
		}
		else {
			insertError(linenum, "k");
			//error << linenum << " k\n";
		}
	}
	//out << "<����˵��>\n";
}

void varDef() {
	string name;
	if (composition[position][0] == "6" || composition[position][0] == "7") {
		string type =  composition[position][0];
		string sigType;
		if (type == "6") {
			sigType = "int";
		}
		else {
			sigType = "char";
		}
		output();//output type
		position++;
		while (1) {
			if (composition[position][0] == "1") {//��ʶ��
				int line=0, row;
				name = composition[position][1];
				std::transform(name.begin(), name.end(), name.begin(), ::tolower);
				if (nameDupError(name)) {
					insertError(composition[position][3], "b");
					//error << composition[position][3] << " b\n";
				}
				output();//output IDENFR
				position++;
				if (composition[position][0] == "36") {//[
					output();//output [
					position++;
					line = atoi(composition[position][1].c_str());
					unIntDef();//int
					if (composition[position][0] == "37") {//]
						output();//output ]
						position++;
					}
					else {
						insertError(composition[position][3], "m");
					}
					if (composition[position][0] == "36") {//[
						output();//output [
						position++;
						row = atoi(composition[position][1].c_str());
						unIntDef();//int
						vector<string> temp;
						temp.push_back(composition[position][3]);
						temp.push_back("2array");
						temp.push_back(sigType);
						temp.push_back(name);
						signary.push_back(temp);
						if (composition[position][0] == "37") {//]
							output();//output ]
							generate_2array(name, type, line, row);
							position++;
						}
						else {
							insertError(composition[position][3], "m");
							//error << composition[position][3] << " m\n";
						}
						if (composition[position][0] == "31") {//= ���������ʼ��
							output();//output =
							position++;
							varInitial(name,2, line, row, type);
							//out << "<�������弰��ʼ��>\n";
							if (composition[position][0] != "33") {
								break;
							}
						}
						else if (composition[position][0] == "33") {
							output();
							position++;
						}
						else if (composition[position][0] != "33") {
							//out << "<���������޳�ʼ��>\n";
							break;
						}

					}
					
					else if (composition[position][0] == "31") {//�����г�ʼ��
						generate_1array(name, sigType, line);
						vector<string> temp;
						temp.push_back(composition[position][3]);
						temp.push_back("1array");
						temp.push_back(sigType);
						temp.push_back(name);
						signary.push_back(temp);
						output();
						position++;
						varInitial(name,1, line, 0, type);
						//out << "<�������弰��ʼ��>\n";
						break;
						
					}
					else if (composition[position][0] == "33") {
						generate_1array(name, sigType, line);
						vector<string> temp;
						temp.push_back(composition[position][3]);
						temp.push_back("1array");
						temp.push_back(sigType);
						temp.push_back(name);
						signary.push_back(temp);
						output();
						position++;
					}
					else if (composition[position][0] != "33") {
						generate_1array(name, sigType, line);
						vector<string> temp;
						temp.push_back(composition[position][3]);
						temp.push_back("1array");
						temp.push_back(sigType);
						temp.push_back(name);
						signary.push_back(temp);
						//out << "<���������޳�ʼ��>\n";
						/*output();//output ;
						position++;*/
						break;
					}

				}
				else if (composition[position][0] == "31") {
					vector<string> temp;
					temp.push_back(composition[position][3]);
					temp.push_back("var");
					temp.push_back(sigType);
					temp.push_back(name);
					signary.push_back(temp);
					output();//output =
					position++;
					string value = varInitial(name,0, 0, 0, type);
					generate_Var(sigType, name, value);
					//out << "<�������弰��ʼ��>\n";
					if (composition[position][0] == "32") {
						break;
					}
				}
				
				else if (composition[position][0] == "33") {
					vector<string> temp;
					temp.push_back(composition[position][3]);
					temp.push_back("var");
					temp.push_back(sigType);
					temp.push_back(name);
					signary.push_back(temp);
					generate_Var(sigType, name, "null");
					output();//output 
					position++;
				}
				else if (composition[position][0] != "33") {
				vector<string> temp;
				temp.push_back(composition[position][3]);
				temp.push_back("var");
				temp.push_back(sigType);
				temp.push_back(name);
				signary.push_back(temp);
				generate_Var(sigType, name, "null");
				//out << "<���������޳�ʼ��>\n";
				/*output();//output ;
				position++;*/
				break;
				}
				
			}
		}
	}
	//out << "<��������>\n";
}

string varInitial(string name,int dimension, int line, int row,string type) {
	string ret = "null";
	if (type == "6") {
		if (dimension == 0) {
			if (composition[position][0] == "2" || composition[position][0] == "20"
				|| composition[position][0] == "21") {
				ret = intDef();
				//out << "<����>\n";
			}
			else {
				if (composition[position][0] == "3") {
					charDef();
					//out << "<����>\n";
					insertError(composition[position][3], "o");
					//error << composition[position][3] << " o\n";
				}
			}
		}
		else if (dimension == 1) {
			int sumline = 0;
			if (composition[position][0] == "38") {//{�Ҵ�����
				output();//output {
				position++;
				sumline++;
				if (composition[position][0] == "2" || composition[position][0] == "20"
					|| composition[position][0] == "21") {
					string value = intDef();
					generate_1arrary_init(name, "int", sumline - 1, value);
					//out << "<����>\n";
				}
				else {
					charDef();
					//out << "<����>\n";
					insertError(composition[position][3], "o");
					//error << composition[position][3] << " o\n";
				}
				while (composition[position][0] == "33") {
					sumline++;
					output();//output ,
					position++;
					if (composition[position][0] == "2" || composition[position][0] == "20"
						|| composition[position][0] == "21") {
						string value = intDef();
						generate_1arrary_init(name, "int", sumline - 1, value);
						//out << "<����>\n";
					}
					else {
						charDef();
						//out << "<����>\n";
						insertError(composition[position][3], "o");
						//error << composition[position][3] << " o\n";
					}
				}
				if (composition[position][0] == "39") {
					output();//output }
					position++;
				}
				if (sumline != line) {
					insertError(composition[position][3], "n");
					//error<< composition[position][3] << " n\n";
				}
			}
		}
		else if (dimension == 2) {
		if (composition[position][0] == "38") {//{�Ҵ�����
			int sumline = 1;
			output();//output {
			position++;
			while (composition[position][0] == "38") {
				int sumrow = 0;
				output();
				position++;
				sumrow++;
				if (composition[position][0] == "2" || composition[position][0] == "20"
					|| composition[position][0] == "21") {
					string x = intDef();
					generate_2array_init(name, "int", sumline - 1, sumrow - 1, x);
					//out << "<����>\n";
				}
				else {
					charDef();
					insertError(composition[position][3], "o");
					//error << composition[position][3] << " o\n";
				}
				while (composition[position][0] == "33") {
					output();//output ,
					position++;
					sumrow++;
					if (composition[position][0] == "2" || composition[position][0] == "20"
						|| composition[position][0] == "21") {
						string x = intDef();
						generate_2array_init(name, "int", sumline - 1, sumrow - 1, x);
						//out << "<����>\n";
					}
					else {
						charDef();
						insertError(composition[position][3], "o");
						//error << composition[position][3] << " o\n";
					}
				}
				if (composition[position][0] == "39") {
					if (sumrow != row) {
						insertError(composition[position][3], "n");
						//error << composition[position][3] << " n\n";
					}
					output();//output }
					position++;
					if (composition[position][0] == "33") {
						sumline++;
						output();//output ,
						position++;
					}
					else if (composition[position][0] == "39") {
						if (sumline != line) {
							insertError(composition[position][3], "n");
							//error << composition[position][3] << " n\n";
						}
						output();//output }
						position++;
						break;
					}
				}
			}

		}
		}
	}
	else {//char 
	if (dimension == 0) {
		if (composition[position][0] == "3") {
			ret = composition[position][1];
			output();//output number

			//out << "<����>\n";
			position++;
		}
		else {
			intDef();
			//out << "<����>\n";
			insertError(composition[position][3], "o");
			//error << composition[position][3] << " o\n";
		}
	}
	else if (dimension == 1) {
		int linenum = 0;
		if (composition[position][0] == "38") {//{�Ҵ�����
			output();//output {
			position++;
			linenum++;
			if (composition[position][0] == "3") {
				generate_1arrary_init(name, "char", linenum - 1, composition[position][1]);
				charDef();//char
				//out << "<����>\n";
			}
			else {
				intDef();
				//out << "<����>\n";
				insertError(composition[position][3], "o");
				//error << composition[position][3] << " o\n";
			}
			
			while (composition[position][0] == "33") {
				output();//output ,
				position++;
				linenum++;
				if (composition[position][0] == "3") {
					generate_1arrary_init(name, "char", linenum - 1, composition[position][1]);
					charDef();//char
					//out << "<����>\n";
				}
				else {
					intDef();
					//out << "<����>\n";
					insertError(composition[position][3], "o");
					//error << composition[position][3] << " o\n";
				}
			}
			if (composition[position][0] == "39") {
				if (linenum != line) {
					insertError(composition[position][3], "n");
					//error << composition[position][3] << " n\n";
				}
				output();//output }
				position++;
			}
		}
	}
	else if (dimension == 2) {
		int linenum = 1;
		if (composition[position][0] == "38") {//{�Ҵ�����
			output();//output {
			position++;
			while (composition[position][0] == "38") {
				int rownum = 0;
				output();
				position++;
				rownum++;
				if (composition[position][0] == "3") {
					generate_2array_init(name, "char", linenum-1, rownum - 1, composition[position][1]);
					charDef();//����
				}
				else {
					intDef();
					insertError(composition[position][3], "o");
					//error << composition[position][3] << " o\n";
				}
				//out << "<����>\n";
				while (composition[position][0] == "33") {
					rownum++;
					output();//output ,
					position++;
					if (composition[position][0] == "3") {
						generate_2array_init(name, "char", linenum - 1, rownum - 1, composition[position][1]);
						charDef();//����
					}
					else {
						intDef();
						insertError(composition[position][3], "o");
						//error << composition[position][3] << " o\n";
					}
					//out << "<����>\n";
				}
				if (composition[position][0] == "39") {
					if (rownum != row) {
						insertError(composition[position][3], "n");
						//error << composition[position][3] << " n\n";
					}
					output();//output }
					position++;
					if (composition[position][0] == "33") {
						linenum++;
						output();//output ,
						position++;
					}
					else if (composition[position][0] == "39") {
						if (linenum != line) {
							insertError(composition[position][3], "n");
							//error << composition[position][3] << " \n";
						}
						output();//output }
						position++;
						break;
					}
				}
			}

		}
	}
	}
	return ret;
}

//�������
void compState() {
	if (composition[position][0] == "5") {
		constState();
	}
	if ((composition[position][0] == "6" || composition[position][0] == "7")
		&& composition[position + 1][0] == "1" && composition[position + 2][0] != "34"){
		varState();
	}
	senList();
	//out << "<�������>\n";
}
//�����
void senList() {
	while (sentence()) {
	}
	//out << "<�����>\n";
}
//���
bool sentence() {
	if (composition[position][0] == "16" || composition[position][0] == "15") {
		looper();
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "10") {
		ifState();
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "1" && composition[position + 1][0] == "34") {
		string linenum = composition[position][3];
		FunCall();
		if (composition[position][0] == "32") {
			output();
			position++;
		}
		else {
			insertError(linenum, "k");
			//error << linenum << " k\n";
		}
		//out << "<���>\n";
		return true;
	}
    else if(composition[position][0] == "1" && (composition[position+1][0] == "31" ||
											composition[position+1][0] == "36")){
		string linenum = composition[position][3];
		assignState();
		if (composition[position][0] == "32") {
		output();
		position++;
		}
		else {
			insertError(linenum, "k");
			//error << linenum << " k\n";
		}
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "17") {
		string linenum = composition[position][3];
		readState();
		if (composition[position][0] == "32") {
			output();
			position++;
		}
		else {
			insertError(linenum, "k");
			//error << linenum << " k\n";
		}
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "18") {
		string linenum = composition[position][3];
		printState();
		if (composition[position][0] == "32") {
			output();
			position++;
		}
		else {
			insertError(linenum, "k");
			//error << linenum << " k\n";
		}
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "12") {
		switchState();
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "32") {
		output();
		position++;
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "19") {
		string linenum = composition[position][3];
		returnState();
		if (composition[position][0] == "32") {
			output();
			position++;
		}
		else {
			insertError(linenum, "k");
			//error << linenum << " k\n";
		}
		//out << "<���>\n";
		return true;
	}
	else if (composition[position][0] == "38") {
		output();
		position++;
		senList();
		if (composition[position][0] == "39") {
			output();
			position++;
			//out << "<���>\n";
			return true;
		}
	}
	return false;
}


void switchState() {
	string type;
	casecount = 0;
	if (composition[position][0] == "12") {//switch
		string linenum = composition[position][3];
		output();
		position++;
		if (composition[position][0] == "34") {//(
			output();
			position++;
			type = expression();
			generate_switch(type,varStack[varStack.size()-1]);
			if (composition[position][0] == "35") {//)
				output();
				position++;
			}
			else {
				insertError(linenum, "l");
				//error << linenum << " l\n";
			}
			if (composition[position][0] == "38") {//{
				output();
				position++;
				caseList(type);
				defaultState();
				if (composition[position][0] == "39") {
					output();
					position++;
				}
			}
		}
	}
	generate_end_switch("switch_" + to_string(switchcount) + "_end");
	switchcount++;
	//out << "<������>\n";
}

void defaultState() {
	generate_default();
	if (composition[position][0] == "14") {
		output();
		position++;
		if (composition[position][0] == "30") {
			output();
			position++;
			if (sentence()) {
				//right
			}
			else {
				insertError(composition[position][3], "k");
			}
		}
		generate_end_default();
		//out << "<ȱʡ>\n";
	}
	else {
		insertError(composition[position][3], "p");
		//error << composition[position][3] << " p\n";
	}
}

void caseList(string type) {
	while (composition[position][0] == "13") {
		caseSen(type);
		casecount++;
	}
	//out << "<�����>\n";
}

void caseSen(string type) {
	if (composition[position][0] == "13") {//case
		output();
		position++;
		if (composition[position][0] == "2" || composition[position][0] == "20" ||
			composition[position][0] == "21") {
			if (type == "char") {
				insertError(composition[position][3], "o");
				//error << composition[position][3] << " o\n";
			}
			string x = intDef();
			generate_case(type, x, "switch_" + to_string(switchcount) + "_case_" + to_string(casecount) + "_end");
			//out << "<����>\n";
			if (composition[position][0] == "30") {//:
				output();
				position++;
				if (sentence()) {
					//right
				}
				else {
					insertError(composition[position][3], "k");
				}
			}
		}
		else if (composition[position][0] == "3") {
			if (type == "int") {
				insertError(composition[position][3], "o");
				//error << composition[position][3] << " o\n";
			}
			generate_case(type, composition[position][1], "switch_" + to_string(switchcount) + "_case_" + to_string(casecount) + "_end");
			charDef();
			//out << "<����>\n";
			if (composition[position][0] == "30") {//:
				output();
				position++;
				if (sentence()) {
					//right
				}
				else {
					insertError(composition[position][3], "k");
				}
			}
		}
	}
	generate_end_case("switch_" + to_string(switchcount) + "_case_" + to_string(casecount) + "_end","switch_"+to_string(switchcount)+"_end");
	//out << "<��������>\n";
}
//�������
void returnState() {
	if (composition[position][0] == "19") {
		output();
		position++;
		string type = "void";
		vector<string> temp;
		if (composition[position][0] == "34") {
			if (funType == "void") {
				insertError(composition[position][3], "g");
				//error << composition[position][3] << " g\n";
			}
			output();
			position++;
			
			type = expression();
			temp = varStack[varStack.size() - 1];
			if (type != funType) {
				insertError(composition[position][3], "h");
				//error << composition[position][3] << " h\n";
			}
			if (composition[position][0] == "35") {
				output();
				position++;
			}
			else {
				insertError(composition[position][3], "l");
				//error << composition[position][3] << " l\n";
			}
		}
		else if (composition[position][0] == "32"){
			if (funType != "void") {
				insertError(composition[position][3], "h");
			}
		}
		generate_ret(type, temp);
	}
	ifReturn = 1;
	//out << "<�������>\n";
}
//д���
void printState() {
	string str;
	if (composition[position][0] == "18") {
		output();
		position++;
		if (composition[position][0] == "34") {
			output();
			position++;
			if (composition[position][0] == "4") {
				str = composition[position][1];
				generate_print_str(str);
				output();
				//out << "<�ַ���>\n";
				position++;
				if (composition[position][0] == "33") {
					output();
					position++;
					string type = expression();
					generate_print_var(varStack[varStack.size()-1],type);
					generate_print_str("\n");
					if (composition[position][0] == "35") {
						output();
						position++;
					}
					else {
						insertError(composition[position][3], "l");
						//error << composition[position][3] << " l\n";
					}
				}
				else if (composition[position][0] == "35") {
					generate_print_str("\n");
					output();
					position++;
				}
				else {
					insertError(composition[position][3], "l");
					//error << composition[position][3] << " l\n";
				}
			}
			else {
				string type =expression();
				generate_print_var(varStack[varStack.size() - 1],type);
				generate_print_str("\n");
				if (composition[position][0] == "35") {
					output();
					position++;
				}
				else {
					insertError(composition[position][3], "l");
					//error << composition[position][3] << " l\n";
				}
			}
		}
	}
	//out << "<д���>\n";
}
//�����
void readState() {
	if (composition[position][0] == "17") {
		output();
		position++;
		if (composition[position][0] == "34") {
			output();
			position++;
			if (composition[position][0] == "1") {
				int namePosition = callName();
				if (namePosition == -1) {
					insertError(composition[position][3], "c");
					//error << composition[position][3] << " c\n";
				}
				else if (signary[namePosition][1] == "const") {
					insertError(composition[position][3], "j");
					//error << composition[position][3] << " j\n";
				}
				generate_read(composition[position][1],signary[namePosition][2]);
				output();
				position++;
				if (composition[position][0] == "35") {
					output();
					position++;
				}
				else {
					insertError(composition[position][3], "l");
					//error << composition[position][3] << " l\n";
				}
			}
		}
	}
	//out << "<�����>\n";
}
//��ֵ���

void assignState() {
	if (composition[position][0] == "1") {//biaozhifu
		int namePosition = callName();
		if (namePosition != -1) {
			if (signary[namePosition][1] == "const") {
				insertError(composition[position][3], "j");
				//error << composition[position][3] << " j\n";
			}
		}
		string name = signary[namePosition][3];
		vector<string> info1;
		vector<string> info2;
		output();
		position++;
		if (composition[position][0] == "31") {// =
			output();
			position++;
			expression();
			generate_assign(name,info1,info2,varStack[varStack.size()-1]);
		}
		else if (composition[position][0] == "36") {// [
			output();
			position++;
			expression();
			info1 = varStack[varStack.size() - 1];
			if (composition[position][0] == "37") {// ]
				output();
				position++;
			}
			else {
				insertError(composition[position][3], "m");
				//error << composition[position][3] << " m\n";
			}
			if (composition[position][0] == "31") {// =
				output();
				position++;
				expression();
				generate_assign(name, info1, info2, varStack[varStack.size() - 1]);
			}
			else if (composition[position][0] == "36") {// [
				output();
				position++;
				expression();
				info2 = varStack[varStack.size() - 1];
				if (composition[position][0] == "37") {// ]
					output();
					position++;
				}
				else {
					insertError(composition[position][3], "m");
					//error << composition[position][3] << " m\n";
				}
				if (composition[position][0] == "31") {// =
					output();
					position++;
					expression();
					generate_assign(name, info1, info2, varStack[varStack.size() - 1]);
				}
			}
		}
	}
	//out << "<��ֵ���>\n";
}
//ѭ�����
void looper() {
	if (composition[position][0] == "15") {//while
		string beginlabel = "while_" + to_string(whilecount) + "_begin";
		string endlabel = "while_" + to_string(whilecount) + "_end";
		generate_looper("while", beginlabel, endlabel);
		whilecount++;
		output();//output while
		position++;
		string linenum = composition[position][3];
		if (composition[position][0] == "34") {//(
			output();//output (
			position++;
			condition();
			if (composition[position][0] == "35") {
				output();
				position++;
			}
			else {
				insertError(linenum, "l");
				//error << linenum << " l\n";
			}
			if (sentence()) {
				//right
			}
			else {
				insertError(composition[position][3], "k");
			}
		}
		generate_end_looper("while",beginlabel,endlabel);
	}
	else if (composition[position][0] == "16") {
		string beginlabel = "for_" + to_string(forcount) + "_begin";
		string endlabel = "for_" + to_string(forcount) + "_end";
		generate_looper("for",beginlabel,endlabel);
		forcount++;
		output();
		position++;
		if (composition[position][0] == "34") {
			output();
			position++;
			if (composition[position][0] == "1") {
				callName();
				string name = composition[position][1];
				std::transform(name.begin(), name.end(), name.begin(), ::tolower);
				output();
				position++;
				if (composition[position][0] == "31") {
					output();
					position++;
					expression();
					generate_for_one(name, varStack[varStack.size() - 1]);
				}
			}
		}

		if (composition[position][0] == "32") {
			output();
			position++;
		}
		else {
			insertError(composition[position][3], "k");
			//error << composition[position][3] << " k\n";
		}
		condition();
		if (composition[position][0] == "32") {
			output();
			position++;
		}
		else {
			insertError(composition[position][3], "k");
			//error << composition[position][3] << " k\n";
		}
		string linenum = composition[position][3];
		if (composition[position][0] == "1") {
			string name1 = composition[position][1];
			std::transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
			callName();
			output();
			position++;
			if (composition[position][0] == "31") {
				output();
				position++;
				if (composition[position][0] == "1") {
					string name2 = composition[position][1];
					std::transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
					callName();
					output();
					position++;
					if (composition[position][0] == "20" || composition[position][0] == "21") {
						string op = composition[position][1];
						output();
						position++;
						string step = composition[position][1];
						stepLen();
						generate_for_three(name1, name2, op, step);
						if (composition[position][0] == "35") {
							output();
							position++;
						}
						else {
							insertError(linenum, "l");
							//error << linenum << " l\n";
						}
						if (sentence()) {
							//right
						}
						else {
							insertError(composition[position][3], "k");
						}
					}
				}
			}
		}
		generate_end_looper("for", beginlabel, endlabel);
	}
	
	//out << "<ѭ�����>\n";
}
//�������
void ifState() {
	string elselabel = "else_" + to_string(ifcount);
	string endlabel = "end_if_" + to_string(ifcount);
	ifcount++;
	if (composition[position][0] == "10") {
		string linenum = composition[position][3];
		output();
		position++;
		generate_if(elselabel, endlabel);
		if (composition[position][0] == "34") {
			output();
			position++;
			condition();
		}
		if (composition[position][0] == "35") {
			output();
			position++;
		}
		else {
			insertError(linenum, "l");
			//error << linenum << " l\n";
		}
		if (sentence()) {
			//right
		}
		else {
			insertError(composition[position][3], "k");
		}
		generate_end_ifpart(elselabel,endlabel);
		if (composition[position][0] == "11") {
			generate_else(elselabel, endlabel);
			output();
			position++;
			if (sentence()) {
				//right
			}
			else {
				insertError(composition[position][3], "k");
			}
			generate_end_if_else(elselabel,endlabel);
		}
		else {
			generate_end_if(elselabel, endlabel);
		}
	}
	
	//out << "<�������>\n";
}
//����
void stepLen() {
	unIntDef();
	//out << "<����>\n";
}
//����
void condition() {
	string type1 = expression();
	string op;
	vector<string> left = varStack[varStack.size() - 1];
	string linenum = composition[position][3];
	if (composition[position][0] == "24" ||
		composition[position][0] == "25" ||
		composition[position][0] == "26" ||
		composition[position][0] == "27" ||
		composition[position][0] == "28" ||
		composition[position][0] == "29") {
		op = composition[position][1];
		output();
		position++;
	}
	string type2 = expression();
	vector<string> right = varStack[varStack.size() - 1];
	generate_condition(left, op, right);
	if (type1 =="char"|| type2 == "char") {
		insertError(linenum, "f");
		//error << linenum << " f\n";
	}
	//out << "<����>\n";

}
//���ʽ

void dosomthing(string op) {
	int size = varStack.size();
	generate_cal("t" + to_string(factorCount), varStack[size - 2][1], op, varStack[size - 1][1], varStack[size - 2][0], varStack[size - 1][0]);
	varStack.pop_back();
	varStack.pop_back();
	vector<string> tempvar;
	tempvar.push_back("1");
	tempvar.push_back("t" + to_string(factorCount));
	varStack.push_back(tempvar);
	factorCount++;
}

string expression() {//1 int 2 char
	string type;
	if (composition[position][0] == "20" || composition[position][0] == "21") {
		string op1 = composition[position][1];
		output();//
		position++;
		iterm();
		int size = varStack.size();
		generate_cal("t" + to_string(factorCount), "0", op1, varStack[size - 1][1], "2", varStack[size - 1][0]);
		varStack.pop_back();
		vector<string> tempvar;
		tempvar.push_back("1");
		tempvar.push_back("t" + to_string(factorCount));
		varStack.push_back(tempvar);
		factorCount++;
		//generate_cal("t" + to_string(factorCount), "0", op1, "t" + to_string(factorCount));
		while (composition[position][0] == "20" || composition[position][0] == "21") {
			string op2 = composition[position][1];
			output();//+-
			position++;
			iterm();
			dosomthing(op2);
			//generate_cal("t" + to_string(factorCount - 1), "t" + to_string(factorCount - 1), op2,"t" + to_string(factorCount));
		}
		return "int";//1 int
	}
	else {
		type = iterm();
		if (composition[position][0] == "20" || composition[position][0] == "21") {
			while (composition[position][0] == "20" || composition[position][0] == "21") {
				string op = composition[position][1];
				output();//+-
				position++;
				iterm();
				dosomthing(op);
				//generate_cal("t" + to_string(factorCount - 1), "t" + to_string(factorCount - 1), op, "t" + to_string(factorCount));
			}
			type = "int";
		}
		
	}
	//out << "<���ʽ>\n";
	return type;
}
//��
string iterm() {
	
	string type = factor();
	if (composition[position][0] == "22" || composition[position][0] == "23") {
		while (composition[position][0] == "22" || composition[position][0] == "23") {
			string op = composition[position][1];
			output();
			position++;
			factor();
			dosomthing(op);
			//generate_cal("t" + to_string(factorCount - 1), "t" + to_string(factorCount - 1), op, "t" + to_string(factorCount));
		}
		type = "int";
	}
	//out << "<��>\n";
	return type;
}
//����
string factor() {//1 int 2 char
	
	string type = "int";
	if (composition[position][0] == "1" && composition[position+1][0] == "36") {//IDENFR
		int namePosition = callName();
		if (namePosition != -1) {
			if (signary[namePosition][2] == "char") {
				type=  "char";//1 int 2char
			}
		}
		output();
		position++;
		if (composition[position][0] == "36") {
			output();
			position++;
			string factorType = expression();
			string linevar = varStack[varStack.size() - 1][1];
			string linetype = varStack[varStack.size() - 1][0];
			if (factorType != "int") {
				insertError(composition[position][3], "i");
				//error << composition[position][3] << " i\n";
			}
			if (composition[position][0] == "37") {
				output();
				position++;
			}
			else {
				insertError(composition[position][3], "m");
				//error << composition[position][3] << " m\n";
			}
			if (composition[position][0] == "36") {
				output();
				position++;
				factorType = expression();
				string rowvar = varStack[varStack.size() - 1][1];
				string rowtype = varStack[varStack.size() - 1][0];
				vector<string> varTemp;
				varTemp.push_back("1");
				varTemp.push_back(signary[namePosition][3]);
				varTemp.push_back(linetype);
				varTemp.push_back(linevar);
				varTemp.push_back(rowtype);
				varTemp.push_back(rowvar);
				generate_load_array("t" + to_string(factorCount), varTemp);
				varStack.pop_back();
				varStack.pop_back();
				varTemp.clear();
				varTemp.push_back("1");
				varTemp.push_back("t" + to_string(factorCount));
				varStack.push_back(varTemp);
				factorCount++;

				if (factorType != "int") {
					insertError(composition[position][3], "i");
					//error << composition[position][3] << " i\n";
				}
				if (composition[position][0] == "37") {
					output();
					position++;
				}
				else {
					insertError(composition[position][3], "m");
					//error << composition[position][3] << " m\n";
				}
			}
			else {//��һά����
				vector<string> varTemp;
				varTemp.push_back("1");
				varTemp.push_back(signary[namePosition][3]);
				varTemp.push_back(linetype);
				varTemp.push_back(linevar);
				generate_load_array("t" + to_string(factorCount), varTemp);
				varStack.pop_back();
				varTemp.clear();
				varTemp.push_back("1");
				varTemp.push_back("t" + to_string(factorCount));
				varStack.push_back(varTemp);
				factorCount++;
			}
		}
		
	}
	else if (composition[position][0] == "1" && composition[position+1][0] == "34") {
		int varsize = varStack.size();
		int flag = FunCall();
		generate_factor_funcall("t" + to_string(factorCount));
		vector<string> tempvar;
		while (varStack.size() != varsize) {
			varStack.pop_back();
		}
		tempvar.push_back("1");
		tempvar.push_back("t" + to_string(factorCount));
		varStack.push_back(tempvar);
		factorCount++;
		if (flag == 2) {
			type = "char";
		}
	}
	else if (composition[position][0] == "1") {
		int namePosition = callName();
		if (namePosition != -1) {
			vector<string> varTemp;
			varTemp.push_back("1");
			varTemp.push_back(signary[namePosition][3]);
			varStack.push_back(varTemp);
			//generate_lw("t" + to_string(factorCount), signary[namePosition][3]);
			if (signary[namePosition][2] == "char") {
				type = "char";//1 int 2char
			}
		}
		output();
		position++;
	}
	else if (composition[position][0] == "34") {// (
		output();
		position++;
		expression();
		//generate_cal("t" + to_string(stack - 1), "null", "=", "t" + to_string(stack));
		if (composition[position][0] == "35") {
			output();
			position++;
		}
		else {
			insertError(composition[position][3], "l");
			//error << composition[position][3] << " l\n";
		}
	}
	else if (composition[position][0] == "3") {//char
		//output();
		vector<string> varTemp;
		varTemp.push_back("2");
		varTemp.push_back("\'" + composition[position][1] + "\'");
		varStack.push_back(varTemp);
		//generate_li("t" + to_string(factorCount), "\'" + composition[position][1]+"\'");
		position++;
		type = "char";
	}
	else {
		string x = intDef();
		vector<string> varTemp;
		varTemp.push_back("2");
		varTemp.push_back(x);
		varStack.push_back(varTemp);
		//generate_li("t" + to_string(factorCount), x);
	}
	//out << "<����>\n";
	return type;
}
//��������
int FunCall() {
	int type = 1;
	string name = composition[position][1];
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	//generate_funcall(name);
	if (composition[position][0] == "1") {
		int namePosition = callName();
		if (namePosition != -1) {
			if (signary[namePosition][2] == "char") {
				type = 2;//1 int 2char
			}
		}
		output();
		position++;
		if (composition[position][0] == "34") {//function
			output();
			position++;
			if (composition[position][0] == "35"&& namePosition != -1) {
				if (signary[namePosition].size() >= 5) {
					vector<string> temp;
					temp.push_back(composition[position][3]);
					temp.push_back("d");
					errorList.push_back(temp);
				}
				//out << "<ֵ������>\n";
				generate_funcall(name);
				output();
				position++;
			}
			else if (composition[position][0]!= "32"){
				valueList(name,namePosition);
				if (composition[position][0] == "35") {
					output();
					position++;
				}
				else {
					insertError(composition[position][3], "l");
					//error << composition[position][3] << " l\n";
				}
			}
			else {
				insertError(composition[position][3], "l");
				//error << composition[position][3] << " l\n";
			}
		}
	}

	for (int i = 0; i < refunction.size(); i++) {
		if (refunction[i] == name) {
			//out << "<�з���ֵ�����������>\n";
			return type;
		}
	}
	//out << "<�޷���ֵ�����������>\n";
	return 0;
}

//ֵ������
void valueList(string name,int namePosition) {
	vector<string> types;
	string type;
	vector<vector<string>> values;
	type = expression();
	values.push_back(varStack[varStack.size() - 1]);
	types.push_back(type);
	while (composition[position][0] == "33") {
		output();
		position++;
		type = expression();
		values.push_back(varStack[varStack.size() - 1]);
		types.push_back(type);
	}
	int parSize;
	generate_valueList(name,values);
	if (namePosition != -1) {
		parSize = signary[namePosition].size() - 4;
		if (parSize != types.size()) {
			insertError(composition[position][3], "d");
			//error << composition[position][3] << " d\n";
		}
		else {
			for (int i = 0; i < parSize; i++) {
				if (types[i] != signary[namePosition][4 + i]) {
					insertError(composition[position][3], "e");
					//error << composition[position][3] << " \e\n";
					break;
				}
			}
		}
	}
	//out << "<ֵ������>\n";
}
//������
void paraList() {
	string type;
	while (composition[position][0] != "35" && composition[position][0] != "38") {
		if (composition[position][0] == "6" || composition[position][0] == "7") {
			if (composition[position][0] == "6") {
				type = "int";
			}
			else {
				type = "char";
			}
			output();//output int or char
			position++;
			if (composition[position][0] == "1") {//output IDENFR
				string name = composition[position][1];
				string linenum = composition[position][3];
				std::transform(name.begin(), name.end(), name.begin(), ::tolower);
				generate_para(type, name);//������
				signary[funposition-1].push_back(type);
				if (nameDupError(name)) {
					insertError(linenum, "b");
					//error << linenum << " b\n";
				}
				vector<string> parTemp;
				parTemp.push_back(linenum);
				parTemp.push_back("par");
				parTemp.push_back(type);
				parTemp.push_back(name);
				signary.push_back(parTemp);
				output();
				position++;
				if (composition[position][0] == "33") {// ,
					output();
					position++;
				}
			}
		}
	}
	//out << "<������>\n";
}
//�з���ֵ��������
void func() {
	ifReturn = 0;
	string name;
	string linenum;
	
	if (composition[position][0] == "6" || composition[position][0] == "7") {
		vector<string> temp;
		temp.push_back(composition[position][3]);
		temp.push_back("func");
		if (composition[position][0] == "6") {
			temp.push_back("int");
			funType = "int";
		}
		else {
			temp.push_back("char");
			funType = "char";
		}
		output();
		position++;
		if (composition[position][0] == "1") {
			name = composition[position][1];
			linenum = composition[position][3];
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			if (nameDupError(name)) {
				insertError(composition[position][3], "b");
				//error << composition[position][3] << " b\n";
			}
			generate_func(funType, name);
			temp.push_back(name);
			signary.push_back(temp);
			funposition = signary.size();
			output();
			//out << "<����ͷ��>\n";
			refunction.push_back(name);
			position++;
			if (composition[position][0] == "34") {
				string linenum = composition[position][3];
				output();
				position++;
				if (composition[position][0] == "35") {
					//out << "<������>\n";
					output();
					position++;	
					if (composition[position][0] == "38") {
						output();
						position++;
						compState();
						if (ifReturn == 0) {
							insertError(composition[position][3], "h");
							//error << linenum << " h\n";
						}
						if (composition[position][0] == "39") {
							output();
							position++;
						}
					}
				}
				else if (composition[position][0] != "38"){
					paraList();
					if (composition[position][0] == "35") {
						output();
						position++;
					}
					else {
						insertError(linenum, "l");
						//error << linenum << " l\n";
					}
					if (composition[position][0] == "38") {
						output();
						position++;
						compState();
						if (ifReturn == 0) {
							insertError(composition[position][3], "h");
							//error << linenum << " h\n";
						}
						if (composition[position][0] == "39") {
							output();
							position++;
						}
					}
				}
				else {
					insertError(linenum, "l");
					//error << linenum << " l\n";
					if (composition[position][0] == "38") {
						output();
						position++;
						compState();
						if (ifReturn == 0) {
							insertError(composition[position][3], "h");
							//error << linenum << " h\n";
						}
						if (composition[position][0] == "39") {
							output();
							position++;
						}
					}
				}
			}
		}
	}
	while (funposition != signary.size()) {
		signary.pop_back();
	}
	funposition = 0;
	generate_end_func();
	//out << "<�з���ֵ��������>\n";
}
//�޷���ֵ��������
void voidfunc() {
	funType = "void";
	string name;
	if (composition[position][0] == "8") {
		vector<string> temp;
		temp.push_back(composition[position][3]);
		temp.push_back("func");
		temp.push_back("void");
		output();
		position++;
		if (composition[position][0] == "1") {
			name = composition[position][1];
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			if (nameDupError(name)) {
				insertError(composition[position][3], "b");
				//error << composition[position][3] << " b\n";
			}
			generate_func(funType, name);
			temp.push_back(name);
			signary.push_back(temp);
			funposition = signary.size();
			output();
			position++;
			if (composition[position][0] == "34") {
				string linenum = composition[position][3];
				output();
				position++;
				if (composition[position][0] == "35") {
					//out << "<������>\n";
					output();
					position++;
					if (composition[position][0] == "38") {
						output();
						position++;
						compState();
						if (composition[position][0] == "39") {
							output();
							position++;
						}
					}
				}
				else if (composition[position][0] != "38"){
					paraList();
					if (composition[position][0] == "35") {
						output();
						position++;
					}
					else {
						insertError(linenum, "l");
						//error << linenum << " l\n";
					}
					if (composition[position][0] == "38") {
						output();
						position++;
						compState();
						if (composition[position][0] == "39") {
							output();
							position++;
						}
					}
				}
				else {
					insertError(linenum, "l");
					//error << linenum << " l\n";
					if (composition[position][0] == "38") {
						output();
						position++;
						compState();
						if (composition[position][0] == "39") {
							output();
							position++;
						}
					}
				}
			}
		}
	}
	while (funposition != signary.size()) {
		signary.pop_back();
	}
	funposition = 0;
	voidfunction.push_back(name);
	generate_end_func();
	//out << "<�޷���ֵ��������>\n";
}
//main����
void mainFunc() {
	funType = "void";
	output();//output void
	position++;
	output();//output main
	position++;
	generate_func("void", "main");
	output();//output (;
	position++;
	if (composition[position][0] == "35") {
		output();//output )
		position++;
	}
	else {
		insertError(composition[position][3], "l");
		//error << composition[position][3] << " l\n";
	}
	funposition = signary.size();
	output();//output {
	position++;
	compState();
	output();//output }
	position++;
	
	//out << "<������>\n";
}

void output() {
	//out << composition[position][2] << " " << composition[position][1] << "\n";
}

void errorPut() {
	int temp = -1;
	for (int i = 0; i < errorList.size(); i++) {
		int x = atoi(errorList[i][0].c_str());
		//cout << x << " " << temp << endl;
		if (x != temp) {
			error << x << " " << errorList[i][1] << endl;
			temp = x;
		}
	}
}

void errorTest() {
	cout << "signary begin\n";
	for (int i = 0; i < signary.size(); i++) {
		cout << signary[i][3] << " " << signary[i].size() << endl;
	}
	cout << "error list begin\n";
		
	for (int i = 0; i < errorList.size(); i++) {
			cout << errorList[i][0] << " " << errorList[i][1] << endl;
	}
}


