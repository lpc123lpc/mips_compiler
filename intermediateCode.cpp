
#include"intermediatecode.h"
#include<algorithm>
ofstream codeTemp("C:\\Users\\lpc\\Desktop\\tempcode.txt");
vector<vector<string>> interCode;
int x = 0;

void generate_func(string type,string name) {
	vector<string> temp;
	temp.push_back("func");
	temp.push_back(type);
	temp.push_back(name);
	interCode.push_back(temp);
}

void generate_para(string type, string name) {
	vector<string> temp;
	temp.push_back("para");
	temp.push_back(type);
	temp.push_back(name);
	interCode.push_back(temp);
}

void generate_Const(string type, string name, string value) {
	vector<string> temp;
	temp.push_back("const");//0
	temp.push_back(type);//1
	temp.push_back(name);//2
	temp.push_back(value);//3
	interCode.push_back(temp);
}
void generate_Var(string type, string name, string value) {
	vector<string> temp;
	temp.push_back("var");
	temp.push_back(type);
	temp.push_back(name);
	if (type == "int") {
		temp.push_back(value);
	}
	else {
		temp.push_back("\'" + value + "\'");
	}
	interCode.push_back(temp);
}
void generate_read(string name,string type) {
	vector<string> temp;
	temp.push_back("read");
	temp.push_back(type);
	temp.push_back(name);
	interCode.push_back(temp);
}
void generate_print_str(string str) {
	vector<string> temp;
	temp.push_back("printstr");
	if (str != "\n") {
		x++;
		temp.push_back("stri" + to_string(x));
	}
	else {
		temp.push_back("space");
	}
	string strtemp = "";
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '\\') {
			strtemp.append("\\\\");
		}
		else {
			strtemp.push_back(str[i]);
		}
	}
	//cout << strtemp << endl;
	temp.push_back(strtemp);
	
	interCode.push_back(temp);
}

void generate_print_var(vector<string>var,string type) {
	vector<string> temp;
	temp.push_back("printvar");
	temp.push_back(type);
	temp.push_back(var[1]);
	temp.push_back(var[0]);
	interCode.push_back(temp);
}

void generate_cal(string result, string left, string op, string right,string leftType,string rightType) {
	vector<string> temp;
	temp.push_back("cal");
	temp.push_back(result);
	temp.push_back(left);
	temp.push_back(op);
	temp.push_back(right);
	temp.push_back(leftType);
	temp.push_back(rightType);
	interCode.push_back(temp);
}

void generate_assign(string name,vector<string>info1,vector<string> info2,vector<string> right) {
	vector<string> temp;
	temp.push_back("assign");
	temp.push_back(name);
	interCode.push_back(temp);
	if (info1.size() != 0) {
		vector<string> line;
		line.push_back("line");
		line.insert(line.end(), info1.begin(), info1.end());
		interCode.push_back(line);
		if (info2.size() != 0) {
			vector<string> row;
			row.push_back("row");
			row.insert(row.end(), info2.begin(), info2.end());
			interCode.push_back(row);
		}
	}
	interCode.push_back(right);
}

void generate_1array(string name, string type, int line) {
	vector<string> temp;
	temp.push_back("1array");
	temp.push_back(type);
	temp.push_back(name);
	temp.push_back(to_string(line));
	interCode.push_back(temp);
}

void generate_1arrary_init(string name, string type, int position, string value) {
	vector<string> temp;
	temp.push_back("1array_init");
	temp.push_back(type);
	temp.push_back(name);
	temp.push_back(to_string(position));
	temp.push_back(value);
	interCode.push_back(temp);
}

void generate_2array(string name, string type, int line, int row) {
	vector<string> temp;
	temp.push_back("2array");
	temp.push_back(type);
	temp.push_back(name);
	temp.push_back(to_string(line));
	temp.push_back(to_string(row));
	interCode.push_back(temp);
}

void generate_2array_init(string name, string type, int line, int row, string value) {
	vector<string> temp;
	temp.push_back("2array_init");
	temp.push_back(type);
	temp.push_back(name);
	temp.push_back(to_string(line));
	temp.push_back(to_string(row));
	temp.push_back(value);
	interCode.push_back(temp);
}

void generate_looper(string type, string beginlabel, string endlabel) {
	vector<string> temp;
	temp.push_back(type);
	temp.push_back(beginlabel);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_end_looper(string type, string beginlabel, string endlabel) {
	vector<string> temp;
	temp.push_back("end" + type);
	temp.push_back(beginlabel);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_for_one(string name, vector<string> right) {
	vector<string> temp;
	temp.push_back("for_one");
	temp.push_back(name);//x = expression();
	interCode.push_back(temp);
	interCode.push_back(right);//expression µÄÄÚÈÝ
}

void generate_for_three(string name1, string name2, string op, string step) {
	vector<string> temp;
	temp.push_back("for_three");
	temp.push_back(name1);
	temp.push_back(name2);
	temp.push_back(op);//+ - 
	temp.push_back(step);
	interCode.push_back(temp);
}

void generate_condition(vector<string> left, string op, vector<string> right) {
	vector<string> temp;
	temp.push_back("condition");
	temp.push_back(op);
	interCode.push_back(temp);
	interCode.push_back(left);
	interCode.push_back(right);
}

void generate_switch(string type, vector<string>var) {
	vector<string> temp;
	temp.push_back("switch");
	temp.push_back(type);
	interCode.push_back(temp);
	interCode.push_back(var);
}

void generate_case(string type, string value,string caselabel) {
	vector<string> temp;
	temp.push_back("case");
	temp.push_back(type);
	if (type == "char") {
		temp.push_back("\'"+value+"\'");
	}
	else {
		temp.push_back(value);
	}
	temp.push_back(caselabel);
	interCode.push_back(temp);
}

void generate_end_case(string endcase,string endlabel) {
	vector<string> temp;
	temp.push_back("endcase");
	temp.push_back(endcase);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_default() {
	vector<string> temp;
	temp.push_back("default");
	interCode.push_back(temp);
}

void generate_end_default() {
	vector<string> temp;
	temp.push_back("enddefault");
	interCode.push_back(temp);
}

void generate_end_switch(string endlabel) {
	vector<string> temp;
	temp.push_back("endswitch");
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_if(string elselabel, string endlabel) {
	vector<string> temp;
	temp.push_back("if");
	temp.push_back(elselabel);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_end_ifpart(string elselabel, string endlabel) {
	vector<string> temp;
	temp.push_back("ifpart");
	temp.push_back(elselabel);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_else(string elselabel, string endlabel) {
	vector<string> temp;
	temp.push_back("else");
	temp.push_back(elselabel);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_end_if(string elselabel, string endlabel) {
	vector<string> temp;
	temp.push_back("endif");
	temp.push_back(elselabel);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_end_if_else(string elselabel, string endlabel) {
	vector<string> temp;
	temp.push_back("endifelse");
	temp.push_back(elselabel);
	temp.push_back(endlabel);
	interCode.push_back(temp);
}

void generate_funcall(string name) {
	vector<string> temp;
	temp.push_back("funcall");
	temp.push_back(name);
	interCode.push_back(temp);
}

void generate_valueList(string name,vector<vector<string>> values) {
	vector<string> temp;
	temp.push_back("valuelist");
	temp.push_back(name);
	temp.push_back(to_string(values.size()));
	interCode.push_back(temp);
	for (int i = 0; i < values.size(); i++) {
		interCode.push_back(values[i]);
	}
}

void generate_ret(string type, vector<string> retvalue) {
	vector<string> temp;
	temp.push_back("ret");
	if (type == "void") {
		temp.push_back("void");
		interCode.push_back(temp);
	}
	else {
		temp.push_back(type);
		interCode.push_back(temp);
		interCode.push_back(retvalue);
	}
}

void generate_end_func() {
	vector<string> temp;
	temp.push_back("endfunc");
	interCode.push_back(temp);
}

void generate_end_main() {
	vector<string> temp;
	temp.push_back("endmain");
	interCode.push_back(temp);
}

void generate_factor_funcall(string var) {
	vector<string> temp;
	temp.push_back("funfactor");
	temp.push_back(var);
	interCode.push_back(temp);
}

void generate_load_array(string result, vector<string> arrayword) {
	vector<string> temp;
	temp.push_back("loadarray");
	temp.push_back(result);
	interCode.push_back(temp);
	interCode.push_back(arrayword);
}

void generate_j_main() {
	vector<string> temp;
	temp.push_back("jmain");
	interCode.push_back(temp);
}

void outputcode() {
	for (int i = 0; i < interCode.size(); i++) {
		for (int j = 0; j < interCode[i].size(); j++) {
			codeTemp << interCode[i][j] << " ";
		}
		codeTemp << endl;
	}
}

