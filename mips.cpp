#include"mips.h"
ofstream mips("C:\\Users\\lpc\\Desktop\\mips.txt");
vector<string> text;
vector<string> varSpace;
vector<string> strSpace;
int i;
int flag = 0;//to consider local or global;
int nowfun = 0;
int globalrow;
vector<string> globalvar;
vector<string> localvar;
vector<vector<string>> localarray;
vector<vector<vector<string>>> funVarSpace;
vector<map<string, int>> funVarMap;
vector<map<string, int>> local2array;
map<string, int> global2array;
vector<int> funSpace;
vector<vector<string>> forstep;
int space;
void count_all_var() {
	for (i = 0; i<interCode.size(); i++) {
		if (interCode[i][0] == "func") {
			if (flag == 0) {
				space = 2;
				flag = 1;
			}
			else {
				funSpace.push_back(space);
				space = 2;
			}
			vector<vector<string>>temp;
			funVarSpace.push_back(temp);
			map<string, int> tempMap;
			funVarMap.push_back(tempMap);
			local2array.push_back(tempMap);
		}
		if (flag == 1) {
			if (interCode[i][0] == "const") {
				vector<string> temp;
				temp.push_back(interCode[i][2]);
				temp.push_back(to_string(space));
				funVarSpace[funVarSpace.size() - 1].push_back(temp);
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][2], space));
				space++;
			}
			else if (interCode[i][0] == "var") {
				vector<string> temp;
				temp.push_back(interCode[i][2]);
				temp.push_back(to_string(space));
				funVarSpace[funVarSpace.size() - 1].push_back(temp);
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][2], space));
				space++;
			}
			else if (interCode[i][0] == "cal") {
				vector<string> temp;
				temp.push_back(interCode[i][1]);
				temp.push_back(to_string(space));
				funVarSpace[funVarSpace.size() - 1].push_back(temp);
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][1], space));
				space++;
			}
			else if (interCode[i][0] == "1array") {
				vector<string> temp;
				temp.push_back(interCode[i][2]);
				temp.push_back(to_string(space));
				funVarSpace[funVarSpace.size() - 1].push_back(temp);
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][2], space));
				int line = atoi(interCode[i][3].c_str());
				space = space + line;
			}
			else if (interCode[i][0] == "2array") {
				vector<string> temp;
				temp.push_back(interCode[i][2]);
				temp.push_back(to_string(space));
				funVarSpace[funVarSpace.size() - 1].push_back(temp);
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][2], space));
				int line = atoi(interCode[i][3].c_str());
				int row = atoi(interCode[i][4].c_str());
				//cout << interCode[i][2] << " " << row << endl;
				local2array[local2array.size() - 1].insert(pair<string, int>(interCode[i][2], row));
				space = space + line * row;
			}
			else if (interCode[i][0] ==	 "funfactor") {
				vector<string> temp;
				temp.push_back(interCode[i][1]);
				temp.push_back(to_string(space));
				funVarSpace[funVarSpace.size() - 1].push_back(temp);
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][1], space));
				space++;
			}
			else if (interCode[i][0] == "loadarray") {
				vector<string> temp;
				temp.push_back(interCode[i][1]);
				temp.push_back(to_string(space));
				funVarSpace[funVarSpace.size() - 1].push_back(temp);
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][1], space));
				space++;
			}
			else if (interCode[i][0] == "funfactor") {
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][1], space));
				space++;
			}
			else if (interCode[i][0] == "para") {
				funVarMap[funVarMap.size() - 1].insert(pair<string, int>(interCode[i][2], space));
				space++;
			}
		}
		else {
			if (interCode[i][0] == "2array") {
				int row = atoi(interCode[i][4].c_str());
				global2array.insert(pair<string, int>(interCode[i][2], row));
			}
		}
	}
	funSpace.push_back(space);
	/*map<string, int>::iterator iter;
	for (i = 0; i < funVarMap.size(); i++) {
		for (iter = funVarMap[i].begin(); iter != funVarMap[i].end(); iter++) {
			cout << iter->first << " " << iter->second << endl;
		}
	}*/
	/*cout << global2array.size() << endl;
	for (i = 0; i < interCode.size(); i++) {
		for (int j = 0; j < interCode[i].size(); j++) {
			cout << interCode[i][j] << " ";
		}
		cout << endl;
	}*/
	for (i = 0; i < interCode.size(); i++) {
		for (int j = 0; j < interCode[i].size(); j++) {
			cout << interCode[i][j] << " ";
		}
		cout << endl;
	}
}

void generate_mips() {
	flag = 0;
	nowfun = 0;
	for (i = 0; i < interCode.size(); i++) {
		/*for (int j = 0; j < interCode[i].size(); j++) {
			cout << interCode[i][j] << " ";
		}
		cout << endl;*/
		if (interCode[i][0] == "const") {
			mips_const();
		}
		else if (interCode[i][0] == "var") {
			mips_var();
		}
		else if (interCode[i][0] == "cal") {
			mips_cal();
		}
		else if (interCode[i][0] == "read") {
			mips_read();
		}
		else if (interCode[i][0] == "printstr") {
			mips_printstr();
		}
		else if (interCode[i][0] == "printvar") {
			mips_printvar();
		}
		else if (interCode[i][0] == "assign") {
			mips_assign();
		}
		else if (interCode[i][0] == "func") {
			mips_func();
		}
		else if (interCode[i][0] == "1array"){
			mips_1array();
		}
		else if (interCode[i][0] == "1array_init") {
			mips_1array_init();
		}
		else if (interCode[i][0] == "2array") {
			mips_2array();
		}
		else if (interCode[i][0] == "2array_init") {
			mips_2array_init();
		}
		else if (interCode[i][0] == "loadarray") {
			mips_load_array();
		}
		else if (interCode[i][0] == "if") {
			mips_if();
		}
		else if (interCode[i][0] == "ifpart") {
			mips_ifpart();
		}
		else if (interCode[i][0] == "endif") {
			mips_endif();
		}
		else if (interCode[i][0] == "endifelse") {
			mips_endif_else();
		}
		else if (interCode[i][0] == "else") {
			mips_else();
		}
		else if (interCode[i][0] == "for") {
			mips_for();
		}
		else if (interCode[i][0] == "endfor") {
			mips_end_for();
		}
		else if (interCode[i][0] == "while") {
			mips_while();
		}
		else if (interCode[i][0] == "endwhile") {
			mips_end_while();
		}
		else if (interCode[i][0] == "switch") {
			mips_switch();
		}
		else if (interCode[i][0] == "case") {
			mips_case();
		}
		else if (interCode[i][0] == "endcase") {
			mips_end_case();
		}
		else if (interCode[i][0] == "endswitch") {
			mips_end_switch();
		}
		else if (interCode[i][0] == "valuelist") {
			mips_valuelist();
		}
		else if (interCode[i][0] == "funfactor") {
			mips_funfactor();
		}
		else if (interCode[i][0] == "ret") {
			mips_ret();
		}
		else if (interCode[i][0] == "jmain") {
			text.push_back("j main");
		}
		else if (interCode[i][0] == "funcall") {
			mips_fun_call();
		}
	}
}

void quick() {
	while (interCode[i][0] == "cal" || interCode[i][0] == "loadarray"||interCode[i][0] == "funfactor") {
		if (interCode[i][0] == "cal") {
			mips_cal();
		}
		else if(interCode[i][0] == "loadarray"){
			mips_load_array();
		}
		else {
			mips_funfactor();
		}
		i++;
	}
}

void mips_load_array() {
	string textline;
	string leftname = interCode[i][1];
	int x = getFunSpace();
	int leftposition = getVarPosition(leftname);// 中间变量
	i++;
	string arrayname = interCode[i][1];
	int arrayposition = getVarPosition(arrayname);
	cout << arrayname << " " << arrayposition << endl;
	if (arrayposition == -1) {
		string linevar = interCode[i][3];
		if (interCode[i][2] == "2") {
			textline = "li $t1," + linevar+"#load "+arrayname;
			text.push_back(textline);
		}
		else {
			int lineposition = getVarPosition(linevar);
			if (lineposition == -1) {
				textline = "la $t1," + linevar;
				text.push_back(textline);
				textline = "lw $t1,($t1)";
				text.push_back(textline);
			}
			else {
				int off = (x - lineposition + 1) * 4;
				textline = "lw $t1," + to_string(off) + ",($sp)";
				text.push_back(textline);
			}
		}
		if (interCode[i].size() == 6) {
			string rowvar = interCode[i][5];
			if (interCode[i][4] == "2") {
				textline = "li $t2," + rowvar;
				text.push_back(textline);
			}
			else {
				int rowposition = getVarPosition(rowvar);
				if (rowposition == -1) {
					textline = "la $t2," + rowvar;
					text.push_back(textline);
					textline = "lw $t2,($t2)";
					text.push_back(textline);
				}
				else {
					int off = (x - rowposition + 1) * 4;
					textline = "lw $t2," + to_string(off) + ",($sp)";
					text.push_back(textline);
				}
			}
			map<string, int>::iterator iter = global2array.find(arrayname);
			int rowlen = iter->second;
			textline = "li $t3," + to_string(rowlen);
			text.push_back(textline);
			textline = "mul $t1,$t1,$t3";
			text.push_back(textline);
			textline = "addu $t1,$t1,$t2";
			text.push_back(textline);
		}
		textline = "li $t2,4";
		text.push_back(textline);
		textline = "mul $t1,$t1,$t2";
		text.push_back(textline);
		textline = "lw $t1," + arrayname + "($t1)";
		text.push_back(textline);
	}
	else {
		string linevar = interCode[i][3];
		if (interCode[i][2] == "2") {
			textline = "li $t1," + linevar;
			text.push_back(textline);
		}
		else {
			int lineposition = getVarPosition(linevar);
			if (lineposition == -1) {
				textline = "la $t1," + linevar;
				text.push_back(textline);
				textline = "lw $t1,($t1)";
				text.push_back(textline);
			}
			else {
				int off = (x - lineposition + 1) * 4;
				textline = "lw $t1," + to_string(off) + ",($sp)";
				text.push_back(textline);
			}
		}
		if (interCode[i].size() == 6) {
			string rowvar = interCode[i][5];
			if (interCode[i][4] == "2") {
				textline = "li $t2," + rowvar;
				text.push_back(textline);
			}
			else {
				int rowposition = getVarPosition(rowvar);
				if (rowposition == -1) {
					textline = "la $t2," + rowvar;
					text.push_back(textline);
					textline = "lw $t2,($t2)";
					text.push_back(textline);
				}
				else {
					int off = (x - rowposition + 1) * 4;
					textline = "lw $t2," + to_string(off) + ",($sp)";
					text.push_back(textline);
				}
			}
			map<string, int>::iterator iter = local2array[nowfun].find(arrayname);
			int rowlen = iter->second;
			textline = "li $t3," + to_string(rowlen);
			text.push_back(textline);
			textline = "mul $t1,$t1,$t3";
			text.push_back(textline);
			textline = "addu $t1,$t1,$t2";
			text.push_back(textline);
		}
		textline = "li $t2," + to_string(arrayposition)+"#getspace";
		text.push_back(textline);
		textline = "addu $t1,$t1,$t2";
		text.push_back(textline);
		textline = "li $t2," + to_string(x + 1);
		text.push_back(textline);
		textline = "subu $t1,$t2,$t1";
		text.push_back(textline);
		textline = "li $t2,4";
		text.push_back(textline);
		textline = "mul $t1,$t1,$t2";
		text.push_back(textline);
		textline = "addu $t1, $t1,$sp";
		text.push_back(textline);
		textline = "lw $t1,($t1)";
		text.push_back(textline);
	}
	int off = (x - leftposition + 1) * 4;
	textline = "sw $t1," + to_string(off) + "($sp)";
	text.push_back(textline);
}

void mips_lw(string name,string count) {
	string textline;
	int x = getFunSpace();
	int position = getVarPosition(name);
	if (position == -1) {
		textline = "la $t"+count+"," + name;
		text.push_back(textline);
		textline = "lw $t" + count + ",($t" + count + ")#load "+name;
		text.push_back(textline);
	}
	else {
		int off = (x - position + 1) * 4;
		textline = "lw $t"+count+"," + to_string(off) + "($sp)#load "+name;
		text.push_back(textline);
	}
}

int getFunSpace() {
	int x = funSpace[nowfun];
	return x-1;
}

int getVarPosition(string name) {
	int position = -1;
	map<string, int>::iterator iter = funVarMap[nowfun].find(name);
	if (iter != funVarMap[nowfun].end()) {
		position = iter->second;
	}
	else {
		//cout << "error var" << endl;
	}
	return position;
}

void mips_func() {
	string textline;
	if (flag == 0) {
		flag = 1;
	}
	else {
		int space = getFunSpace();
		space = space * 4;
		textline = "addiu $sp,$sp," + to_string(space);
		text.push_back(textline);
		text.push_back("lw $ra,($sp)");
		text.push_back("jr $ra");
		nowfun++;
	}
	textline = interCode[i][2]+":";
	text.push_back(textline);
	int space = getFunSpace();
	space = space * 4;
	if (interCode[i][0] != "main") {
		textline = "sw $ra,($sp)";
		text.push_back(textline);
	}
	textline = "subi $sp,$sp," + to_string(space);
	text.push_back(textline);
	
}

int getArrayRow(string name,int x) {
	if (x == -1) {
		map<string, int>::iterator iter = global2array.find(name);
		if (iter != global2array.end()) {
			return iter->second;
		}
		else {
			return -1;
		}
	}
	else {
		map<string, int>::iterator iter = local2array[nowfun].find(name);
		if (iter != local2array[nowfun].end()) {
			return iter->second;
		}
		else {
			return -1;
		}
	}
}

void mips_assign() {
	string textline;
	string varname = interCode[i][1];
	int x = getFunSpace();
	int nameposition = getVarPosition(varname);
	i++;
	int fuck = 1;
	if (interCode[i][0] == "line") {
		fuck = 2;
		string linetype = interCode[i][1];//1 or 2
		string linevar = interCode[i][2];
		if (linetype == "1") {
			int position = getVarPosition(linevar);
			if (position == -1) {
				textline = "la $t1," + linevar + "#get global var";
				text.push_back(textline);
				textline = "lw ,$t1,($t1)";
				text.push_back(textline);
			}
			else {
				int off = (x - position + 1) * 4;
				textline = "lw $t1," + to_string(off) + "($sp)";
				text.push_back(textline);
			}
		}
		else {
			textline = "li $t1," + linevar;
			text.push_back(textline);
		}
		i++;
		if (interCode[i][0] == "row") {
			fuck = 3;
			string rowtype = interCode[i][1];
			string rowvar = interCode[i][2];
			if (rowtype == "1") {
				int position = getVarPosition(rowvar);
				if (position == -1) {
					textline = "la $t2," + rowvar + "#get global var";
					text.push_back(textline);
					textline = "lw $t2,($t2)";
					text.push_back(textline);
				}
				else {
					int off = (x - position + 1) * 4;
					textline = "lw $t2," + to_string(off) + "($sp)";
					text.push_back(textline);
				}
			}
			else {
				textline = "li $t2," + rowvar;
				text.push_back(textline);
			}
			i++;
		}
	}
	if (fuck == 3) {
		int rownum = getArrayRow(varname, nameposition);
		textline = "li $t3," + to_string(rownum);
		text.push_back(textline);
		textline = "mul $t1,$t1,$t3";
		text.push_back(textline);
		textline = "addu $t1,$t1,$t2";
		text.push_back(textline);
	}

	if (interCode[i][0] == "2") {
		textline = "li $t2," + interCode[i][1];
		text.push_back(textline);
	}
	else {
		mips_lw(interCode[i][1], "2");
	}

	if (fuck == 1) {
		if (nameposition == -1) {
			textline = "la $t1," + varname;
			text.push_back(textline);
			textline = "sw $t2,($t1)";
			text.push_back(textline);
		}
		else {
			int off = (x - nameposition + 1) * 4;
			textline = "sw $t2," + to_string(off) + "($sp)";
			text.push_back(textline);
		}
	}
	else {
		if (nameposition == -1) {
			textline = "li $t3,4";
			text.push_back(textline);
			textline = "mul $t1,$t1,$t3";
			text.push_back(textline);
			textline = "sw $t2," + varname + "($t1)";
			text.push_back(textline);
		}
		else {
			textline = "li $t3," + to_string(nameposition);
			text.push_back(textline);
			textline = "addu $t1,$t1,$t3";
			text.push_back(textline);
			textline = "li $t3," + to_string(x + 1);
			text.push_back(textline);
			textline = "subu $t1,$t3,$t1";
			text.push_back(textline);
			textline = "li $t3,4";
			text.push_back(textline);
			textline = "mul $t1,$t1,$t3";
			text.push_back(textline);
			textline = "addu $t1,$t1,$sp";
			text.push_back(textline);
			textline = "sw $t2,($t1)";
			text.push_back(textline);
		}
	}
}

void mips_printvar() {
	//type 1 name 2
	string textline;
	if (interCode[i][3] == "2") {
		textline = "li $t1," + interCode[i][2];
		text.push_back(textline);
	}
	else {
		mips_lw(interCode[i][2], "1");
	}
	textline = "move $a0,$t1#print t1";
	text.push_back(textline);
	if (interCode[i][1] == "int") {
		textline = "li $v0,1#print int";
		text.push_back(textline);	
	}
	else {
		textline = "li $v0,11#print char";
		text.push_back(textline);
	}
	text.push_back("syscall");
}

void mips_printstr() {
	if (interCode[i][1] != "space") {
		string  dataline = interCode[i][1] + ":.asciiz \""+interCode[i][2]+"\"";
		strSpace.push_back(dataline);
	}
	string textline = "li $v0,4#print string";
	text.push_back(textline);
	textline = "la $a0," + interCode[i][1];
	text.push_back(textline);
	text.push_back("syscall");
}

void mips_read() {
	string textline;
	if (interCode[i][1] == "int") {
		textline = "li $v0,5#read int";
	}
	else {
		textline = "li $v0,12#read char";
	}
	text.push_back(textline);
	textline = "syscall";
	text.push_back(textline);
	int x = getFunSpace();
	int position = getVarPosition(interCode[i][2]);
	if (position == -1) {
		textline = "la $s1," + interCode[i][2];
		text.push_back(textline);
		textline = "sw $v0,($s1)#store global var";
		text.push_back(textline);
	}
	else {
		int off = x-position+1;
		off = off * 4;
		textline = "sw $v0," + to_string(off) + "($sp)#store local var";
		text.push_back(textline);
	}
}

void mips_cal() {
	string textline;
	// re :1 left:2 op:3 right:4 ltype 5 rtype 6
	if (interCode[i][5] == "1") {
		mips_lw(interCode[i][2],"1");
	}
	else {
		textline = "li $t1," + interCode[i][2];
		text.push_back(textline);
	}

	if (interCode[i][6] == "1") {
		mips_lw(interCode[i][4], "2");
	}
	else {
		textline = "li $t2," + interCode[i][4];
		text.push_back(textline);
	}


	if (interCode[i][3] == "+") {
		textline = "addu $t1,$t1,$t2";
		text.push_back(textline);
	}
	else if (interCode[i][3] == "-") {
		textline = "subu $t1,$t1,$t2";
		text.push_back(textline);
	}
	else if (interCode[i][3] == "*") {
		textline = "mul $t1,$t1,$t2";
		text.push_back(textline);
	}
	else if (interCode[i][3] == "/") {
		textline = "div $t1,$t1,$t2";
		text.push_back(textline);
	}
	else if (interCode[i][3] == "=") {
		textline = "move $" + interCode[i][1] + ",$" + interCode[i][4];
		text.push_back(textline);
	}
	int x = getFunSpace();
	int position = getVarPosition(interCode[i][1]);
	int off = (x - position + 1) * 4;
	textline = "sw $t1,"+to_string(off)+"($sp)#store " + interCode[i][1];
	text.push_back(textline);
}

int getLocalPosition(string name) {
	for (int j = 0; j < localvar.size(); j++) {
		if (localvar[j] == name) {
			return j;
		}
	}
	return -1;
}

void mips_const() {
	string  dataline;
	string textline;
	if (flag == 0) {
		globalvar.push_back(interCode[i][2]);
		dataline = interCode[i][2] + ":.space 4";
		varSpace.push_back(dataline);
		textline = "la $t1," + interCode[i][2] + "#get address and store value";
		text.push_back(textline);
		textline = "li $t2," + interCode[i][3];
		text.push_back(textline);
		textline = "sw $t2,($t1)";
		text.push_back(textline);
	}
	else {
		//localvar.push_back(interCode[i][2]);
		textline = "li $t1," + interCode[i][3];
		text.push_back(textline);
		int x = getFunSpace();
		int position;
		map<string, int>::iterator iter = funVarMap[nowfun].find(interCode[i][2]);
		if (iter != funVarMap[nowfun].end()) {
			position = iter->second;
		}
		else {
			cout << "error const" << endl;
		}
		int off = (x - position + 1) * 4;
		textline = "sw $t1," + to_string(off) + "($sp)#store "+interCode[i][2];
		text.push_back(textline);
	}
}

void mips_var() {
	string dataline;
	string textline;
	if (flag == 0) {
		globalvar.push_back(interCode[i][2]);
		dataline = interCode[i][2] + ":.space 4";
		varSpace.push_back(dataline);
		if ((interCode[i][3] != "null"&& interCode[i][1] == "int")||
			(interCode[i][3] != "\'null\'" && interCode[i][1] == "char")) {
			textline = "la $t1," + interCode[i][2] + "#get address and store value";
			text.push_back(textline);
			textline = "li $t2," + interCode[i][3];
			text.push_back(textline);
			textline = "sw $t2,($t1)";
			text.push_back(textline);
		}
	}
	else {
		//localvar.push_back(interCode[i][2]);
		if ((interCode[i][3] != "null" && interCode[i][1] == "int") ||
			(interCode[i][3] != "\'null\'" && interCode[i][1] == "char")) {
			textline = "li $t1," + interCode[i][3]+"#store local var";
			text.push_back(textline);
			int x = getFunSpace();
			int position;
			map<string, int>::iterator iter = funVarMap[nowfun].find(interCode[i][2]);
			if (iter != funVarMap[nowfun].end()) {
				position = iter->second;
			}
			else {
				cout << "error var" << endl;
			}
			int off = (x - position + 1) * 4;
			textline = "sw $t1," + to_string(off) + "($sp)#store " + interCode[i][2];
			text.push_back(textline);
		}
	}
}

void mips_1array() {
	string dataline;
	string textline;
	if (flag == 0) {
		globalvar.push_back(interCode[i][2]);
		int space = atoi(interCode[i][3].c_str());
		space = space * 4;
		dataline = interCode[i][2] + ":.space " + to_string(space);
		varSpace.push_back(dataline);
	}
	else {
		/*vector<string> temp;
		temp.push_back(interCode[i][2]);
		temp.push_back(to_string(localvar.size()));
		localarray.push_back(temp);*/
	}
}

void mips_1array_init() {
	string textline;
	string var;
	if (interCode[i][1] == "char") {
		var = "\'" + interCode[i][4] + "\'";
	}
	else {
		var = interCode[i][4];
	}
	if (flag == 0) {
		int off = atoi(interCode[i][3].c_str());
		off = off * 4;
		textline = "li $t1," + var + "#init global array";
		text.push_back(textline);
		textline = "li $t2," + to_string(off);
		text.push_back(textline);
		textline = "sw $t1," + interCode[i][2] + "($t2)";
		text.push_back(textline);
	}
	else {
		int off = atoi(interCode[i][3].c_str());
		localvar.push_back(interCode[i][2] + "-" + interCode[i][3]);
		textline = "li $t1," + var + "#init  local array";
		text.push_back(textline);
		int x = getFunSpace();
		int position;
		map<string, int>::iterator iter = funVarMap[nowfun].find(interCode[i][2]);
		if (iter != funVarMap[nowfun].end()) {
			position = iter->second;
		}
		else {
			cout << "error var" << endl;
		}
		position = position + off;
		off = (x - position + 1) * 4;
		textline = "sw $t1," + to_string(off) + "($sp)#store " + interCode[i][2];
		text.push_back(textline);
	}
}

void mips_2array() {
	string dataline;
	string textline;
	int line = atoi(interCode[i][3].c_str());
	int row = atoi(interCode[i][4].c_str());
	if (flag == 0) {
		globalvar.push_back(interCode[i][2]);
		int space = line * row;
		space = space * 4;
		globalrow = row;
		//cout << interCode[i][2] << " fuck" << globalrow << endl;
		dataline = interCode[i][2] + ":.space " + to_string(space);
		varSpace.push_back(dataline);
	}
	else {
		/*vector<string> temp;
		temp.push_back(interCode[i][2]);
		temp.push_back(to_string(localvar.size()));
		temp.push_back(to_string(row));
		localarray.push_back(temp);*/
	}
}

void mips_2array_init() {
	string textline;
	string var;
	if (interCode[i][1] == "char") {
		var = "\'" + interCode[i][5] + "\'";
	}
	else {
		var = interCode[i][5];
	}
	if (flag == 0) {
		int line = atoi(interCode[i][3].c_str());
		int row = atoi(interCode[i][4].c_str());
		int off = line * globalrow + row;
		off = off * 4;
		textline = "li $t1," + var + "#init global array";
		text.push_back(textline);
		textline = "li $t2," + to_string(off);
		text.push_back(textline);
		textline = "sw $t1," + interCode[i][2] + "($t2)";
		text.push_back(textline);
	}
	else {
		int line = atoi(interCode[i][3].c_str());
		int row = atoi(interCode[i][4].c_str());
		
		//localvar.push_back(interCode[i][2] + "-" + interCode[i][3]+"-"+interCode[i][4]);
		textline = "li $t1," + var + "#init  local array";
		text.push_back(textline);
		int x = getFunSpace();
		int position;
		map<string, int>::iterator iter = funVarMap[nowfun].find(interCode[i][2]);
		if (iter != funVarMap[nowfun].end()) {
			position = iter->second;
		}
		else {
			cout << "error var" << endl;
		}
		int rowlen = 0;
		iter = local2array[nowfun].find(interCode[i][2]);
		if (iter != local2array[nowfun].end()) {
			 rowlen=iter->second;
		}
		int off = line * rowlen + row;
		position = position + off;
		off = (x - position + 1) * 4;
		textline = "sw $t1," + to_string(off) + "($sp)#store " + interCode[i][2];
		text.push_back(textline);
	}
}

void mips_if() {
	string elselabel = interCode[i][1];
	string endlabel = interCode[i][2];
	i++;
	string textline;
	quick();
	if (interCode[i][0] == "condition") {
		string op = interCode[i][1];
		i++;
		string lefttype = interCode[i][0];
		string leftvar = interCode[i][1];
		i++;
		string righttype = interCode[i][0];
		string rightvar = interCode[i][1];
		int x = getFunSpace();
		if (lefttype == "2") {
			textline = "li $t1," + leftvar+"#if left";
			text.push_back(textline);
		}
		else {
			int leftpos = getVarPosition(leftvar);
			if (leftpos == -1) {
				textline = "la $t1," + leftvar + "#if left";
				text.push_back(textline);
				textline = "lw $t1,($t1)";
				text.push_back(textline);
			}
			else {
				int off = (x - leftpos + 1) * 4;
				textline = "lw $t1," + to_string(off) + "($sp)#if left";
				text.push_back(textline);
			}
		}

		if (righttype == "2") {
			textline = "li $t2," + rightvar + "#if right";
			text.push_back(textline);
		}
		else {
			int rightpos = getVarPosition(rightvar);
			if (rightpos == -1) {
				textline = "la $t2," + rightvar + "#if right";
				text.push_back(textline);
				textline = "lw $t2,($t2)";
				text.push_back(textline);
			}
			else {
				int off = (x - rightpos + 1) * 4;
				textline = "lw $t2," + to_string(off) + "($sp)#if right";
				text.push_back(textline);
			}
		}
		
		if (op == "==") {
			textline = "bne $t1,$t2," + elselabel;
			text.push_back(textline);
			
		}
		else if (op == "!=") {
			textline = "beq $t1,$t2," + elselabel;
			text.push_back(textline);
		}
		else if (op == ">=") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "bltz $t1," + elselabel;
			text.push_back(textline);
		}
		else if (op == ">") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "blez $t1," + elselabel;
			text.push_back(textline);
		}
		else if (op == "<=") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "bgtz $t1," + elselabel;
			text.push_back(textline);
		}
		else if (op == "<") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "bgez $t1," + elselabel;
			text.push_back(textline);
		}
	}
}

void mips_ifpart() {
	string textline;
	string elselabel = interCode[i][1];
	string endlabel = interCode[i][2];
	textline = "j " + endlabel;
	text.push_back(textline);
}

void mips_else() {
	string textline;
	string elselabel = interCode[i][1];
	string endlabel = interCode[i][2];
	textline = elselabel + ":";
	text.push_back(textline);
}

void mips_endif() {
	string textline;
	string elselabel = interCode[i][1];
	string endlabel = interCode[i][2];
	textline = elselabel + ":";
	text.push_back(textline);
	textline = endlabel + ":";
	text.push_back(textline);
}

void mips_endif_else() {
	string textline;
	string elselabel = interCode[i][1];
	string endlabel = interCode[i][2];
	textline = endlabel + ":";
	text.push_back(textline);
}

void mips_for() {
	string textline;
	string beginlabel = interCode[i][1];
	string endlabel = interCode[i][2];
	//
	i++;
	quick();//for_one
	string varna = interCode[i][1];
	i++;
	int x = getFunSpace();
	string initvartype = interCode[i][0];
	string initvar = interCode[i][1];
	int initposition = getVarPosition(initvar);
	if (initvartype == "2") {
		textline = "li $t1," + initvar;
		text.push_back(textline);
	}
	else {
		if (initposition == -1) {
			textline = "la $t1," + initvar + "#for_one";
			text.push_back(textline);
			textline = "lw $t1,($t1)";
			text.push_back(textline);
		}
		else {
			int off = (x - initposition + 1) * 4;
			textline = "lw $t1," + to_string(off) + "($sp)#for_one";
			text.push_back(textline);
		}
	}
	int naposition = getVarPosition(varna);
	if (naposition == -1) {
		textline = "la $t2," + varna;
		text.push_back(textline);
		textline = "sw $t1,($t2)";
		text.push_back(textline);
	}
	else {
		int off = (x - naposition + 1) * 4;
		textline = "sw $t1," + to_string(off) + "($sp)";
		text.push_back(textline);
	}
	textline = beginlabel + ":";
	text.push_back(textline);
	i++;
	quick();
	if (interCode[i][0] == "condition") {
		string op = interCode[i][1];
		i++;
		string lefttype = interCode[i][0];
		string leftvar = interCode[i][1];
		i++;
		string righttype = interCode[i][0];
		string rightvar = interCode[i][1];
		int x = getFunSpace();
		if (lefttype == "2") {
			textline = "li $t1," + leftvar + "#if left";
			text.push_back(textline);
		}
		else {
			int leftpos = getVarPosition(leftvar);
			if (leftpos == -1) {
				textline = "la $t1," + leftvar + "#if left";
				text.push_back(textline);
				textline = "lw $t1,($t1)";
				text.push_back(textline);
			}
			else {
				int off = (x - leftpos + 1) * 4;
				textline = "lw $t1," + to_string(off) + "($sp)#if left";
				text.push_back(textline);
			}
		}

		if (righttype == "2") {
			textline = "li $t2," + rightvar + "#if right";
			text.push_back(textline);
		}
		else {
			int rightpos = getVarPosition(rightvar);
			if (rightpos == -1) {
				textline = "la $t2," + rightvar + "#if right";
				text.push_back(textline);
				textline = "lw $t2,($t2)";
				text.push_back(textline);
			}
			else {
				int off = (x - rightpos + 1) * 4;
				textline = "lw $t2," + to_string(off) + "($sp)#if right";
				text.push_back(textline);
			}
		}

		if (op == "==") {
			textline = "bne $t1,$t2," + endlabel;
			text.push_back(textline);

		}
		else if (op == "!=") {
			textline = "beq $t1,$t2," + endlabel;
			text.push_back(textline);
		}
		else if (op == ">=") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "bltz $t1," + endlabel;
			text.push_back(textline);
		}
		else if (op == ">") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "blez $t1," + endlabel;
			text.push_back(textline);
		}
		else if (op == "<=") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "bgtz $t1," + endlabel;
			text.push_back(textline);
		}
		else if (op == "<") {
			textline = "subu $t1,$t1,$t2 ";
			text.push_back(textline);
			textline = "bgez $t1," + endlabel;
			text.push_back(textline);
		}
	}
	i++;//for step
	if (interCode[i][0] == "for_three") {
		forstep.push_back(interCode[i]);
	}
	
}

void mips_while() {
	string textline;
	string beginlable = interCode[i][1];
	string endlable = interCode[i][2];
	textline = beginlable + ":#begin while";
	text.push_back(textline);
	i++;
	//condition
	quick();
	string op = interCode[i][1];
	i++;
	string lefttype = interCode[i][0];
	string leftvar = interCode[i][1];
	i++;
	string righttype = interCode[i][0];
	string rightvar = interCode[i][1];
	int x = getFunSpace();
	if (lefttype == "2") {
		textline = "li $t1," + leftvar + "#if left";
		text.push_back(textline);
	}
	else {
		int leftpos = getVarPosition(leftvar);
		if (leftpos == -1) {
			textline = "la $t1," + leftvar + "#if left";
			text.push_back(textline);
			textline = "lw $t1,($t1)";
			text.push_back(textline);
		}
		else {
			int off = (x - leftpos + 1) * 4;
			textline = "lw $t1," + to_string(off) + "($sp)#if left";
			text.push_back(textline);
		}
	}

	if (righttype == "2") {
		textline = "li $t2," + rightvar + "#if right";
		text.push_back(textline);
	}
	else {
		int rightpos = getVarPosition(rightvar);
		if (rightpos == -1) {
			textline = "la $t2," + rightvar + "#if right";
			text.push_back(textline);
			textline = "lw $t2,($t2)";
			text.push_back(textline);
		}
		else {
			int off = (x - rightpos + 1) * 4;
			textline = "lw $t2," + to_string(off) + "($sp)#if right";
			text.push_back(textline);
		}
	}
	if (op == "==") {
		textline = "bne $t1,$t2," + endlable;
		text.push_back(textline);

	}
	else if (op == "!=") {
		textline = "beq $t1,$t2," + endlable;
		text.push_back(textline);
	}
	else if (op == ">=") {
		textline = "subu $t1,$t1,$t2 ";
		text.push_back(textline);
		textline = "bltz $t1," + endlable;
		text.push_back(textline);
	}
	else if (op == ">") {
		textline = "subu $t1,$t1,$t2 ";
		text.push_back(textline);
		textline = "blez $t1," + endlable;
		text.push_back(textline);
	}
	else if (op == "<=") {
		textline = "subu $t1,$t1,$t2 ";
		text.push_back(textline);
		textline = "bgtz $t1," + endlable;
		text.push_back(textline);
	}
	else if (op == "<") {
		textline = "subu $t1,$t1,$t2 ";
		text.push_back(textline);
		textline = "bgez $t1," + endlable;
		text.push_back(textline);
	}

}

void mips_end_while() {
	string beginlabel = interCode[i][1];
	string endlabel = interCode[i][2];
	string textline;
	textline = "j " + beginlabel;
	text.push_back(textline);
	textline = endlabel + ":";
	text.push_back(textline);
}

void mips_end_for() {
	string beginlabel = interCode[i][1];
	string endlabel = interCode[i][2];
	string textline;
	vector<string> stepline = forstep[forstep.size()-1];
	forstep.pop_back();
	string leftvar = stepline[1];
	string rightvar = stepline[2];
	string op = stepline[3];
	string step = stepline[4];
	int x = getFunSpace();
	int rightpos = getVarPosition(rightvar);
	if (rightpos == -1) {
		textline = "la $t1," + rightvar;
		text.push_back(textline);
		textline = "lw $t1,($t1)";
		text.push_back(textline);
		
	}
	else {
		int off = (x - rightpos + 1) * 4;
		textline = "lw $t1," + to_string(off) + "($sp)";
		text.push_back(textline);
	}
	/*textline = "li $t2," + step;
	text.push_back(textline);*/
	if (op == "+") {
		textline = "addiu $t1,$t1,"+ step;
		text.push_back(textline);
	}
	else {
		textline = "subiu $t1,$t1,"+ step;
		text.push_back(textline);
	}
	int leftpos = getVarPosition(leftvar);
	if (leftpos == -1) {
		textline = "la $t2," + leftvar;
		text.push_back(textline);
		textline = "sw $t1,($t2)";
		text.push_back(textline);
	}
	else {
		int off = (x - leftpos + 1) * 4;
		textline = "sw $t1," + to_string(off) + "($sp)";
		text.push_back(textline);
	}
	textline = "j " + beginlabel;
	text.push_back(textline);
	textline = endlabel + ":";
	text.push_back(textline);
}

void mips_switch() {
	string textline;
	string expretype = interCode[i][1];
	i++;
	string vartype = interCode[i][0];
	string varname = interCode[i][1];
	if (vartype == "1") {
		string textline;
		int x = getFunSpace();
		int position = getVarPosition(varname);
		if (position == -1) {
			textline = "la $s1," + varname;
			text.push_back(textline);
			textline = "lw $s1,($s1)#load " + varname;
			text.push_back(textline);
		}
		else {
			int off = (x - position + 1) * 4;
			textline = "lw $s1," + to_string(off) + "($sp)#load " + varname;
			text.push_back(textline);
		}
	}
	else {
		textline = "li $s1," + varname;
		text.push_back(textline);
	}
}

void mips_case() {
	string textline;
	string value = interCode[i][2];
	string endlabel = interCode[i][3];
	
	textline = "li $t1," + value;
	text.push_back(textline);
	textline = "bne $s1,$t1," + endlabel;
	text.push_back(textline);
}

void mips_end_case() {
	string textline;
	string caseend = interCode[i][1];
	string endswitch = interCode[i][2];
	textline = "j " + endswitch;
	text.push_back(textline);
	textline = caseend + ":";
	text.push_back(textline);
}

void mips_end_switch() {
	string textline;
	textline = interCode[i][1] + ":";
	text.push_back(textline);
}

void mips_valuelist() {
	string textline;
	string funame = interCode[i][1];
	int x = atoi(interCode[i][2].c_str());
	for (int j = 0; j < x; j++) {
		i++;
		int off = -4 * (j + 1);
		string type = interCode[i][0];
		string name = interCode[i][1];
		if (type == "2") {
			textline = "li $t1," + name;
			text.push_back(textline);
		}
		else {
			mips_lw(name, "1");
		}
		textline = "sw $t1," + to_string(off) + "($sp)";
		text.push_back(textline);
	}
	textline = "jal " + funame;
	text.push_back(textline);
}

void mips_fun_call() {
	string textline;
	string funname = interCode[i][1];
	textline = "jal " + funname;
	text.push_back(textline);
}

void mips_funfactor() {
	string tempvar = interCode[i][1];
	string textline;
	/*i++;
	while (interCode[i][0] == "cal" || interCode[i][0] == "loadarray") {
		if (interCode[i][0] == "cal") {
			mips_cal();
		}
		else {
			mips_load_array();
		}
		i++;
	}

	if (interCode[i][0] == "valuelist") {
		mips_valuelist();
	}*/
	int x = getFunSpace();
	int posi = getVarPosition(tempvar);
	int off = (x - posi + 1) * 4;
	textline = "sw $v0," + to_string(off) + "($sp)";
	text.push_back(textline);
}

void mips_ret() {
	string textline;
	int x = getFunSpace();
	int off = x * 4;
	if (nowfun == funSpace.size() - 1) {
		textline = "li $v0,10";
		text.push_back(textline);
		textline = "syscall";
		text.push_back(textline);
	}
	else {
		if (interCode[i][1] == "void") {
			textline = "addiu $sp,$sp," + to_string(off);
			text.push_back(textline);
			textline = "lw $ra,($sp)";
			text.push_back(textline);
			text.push_back("jr $ra");
		}
		else {
			i++;
			quick();
			if (interCode[i][0] == "2") {
				textline = "li $v0," + interCode[i][1];
				text.push_back(textline);
			}
			else {
				int pos = getVarPosition(interCode[i][1]);
				if (pos == -1) {
					textline = "la $t1," + interCode[i][1];
					text.push_back(textline);
					textline = "lw $v0,($t1)";
					text.push_back(textline);
				}
				else {
					int off = (1 + x - pos) * 4;
					textline = "lw $v0," + to_string(off) + "($sp)";
					text.push_back(textline);
				}
			}
			textline = "addiu $sp,$sp," + to_string(off);
			text.push_back(textline);
			textline = "lw $ra,($sp)";
			text.push_back(textline);
			text.push_back("jr $ra");
		}
	}
	
	
}

void outputMips() {
	mips << ".data" << endl;
	for (int i = 0; i < varSpace.size(); i++) {
		mips << varSpace[i] << endl;
	}
	mips << "space:.asciiz \"\\n\""<<endl;
	for (int i = 0; i < strSpace.size(); i++) {
		mips << strSpace[i] << endl;
	}

	mips << ".text"<<endl;
	for (int i = 0; i < text.size(); i++) {
		mips << text[i] << endl;
	}
}





