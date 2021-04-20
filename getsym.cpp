#include<cstdio>
#include<cstdlib>
#include<regex>
#include<iostream>
#include<string>
#include<fstream>
#include<iterator>
#include<vector>
#include"getsym.h"

using namespace std;
static string line;
static int position = 0;
int linenum;
vector<vector<string>> composition;
vector<vector<string>> errorList;
fstream f("C:\\Users\\lpc\\Desktop\\testfile.txt");
ofstream error("C:\\Users\\lpc\\Desktop\\error.txt");

void dealOther(int head) {
	while (position < head) {
		vector<string> one;
		//cout << position << line[position]<<endl;
		switch (line[position])
		{
		case ' ':
			position++;
			break;
		case '+':
			position++;
			//cout << "PLUS +\n";
			one.push_back("20");
			one.push_back("+");
			one.push_back("PLUS");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '-':
			position++;
			//out << "MINU -\n";
			one.push_back("21");
			one.push_back("-");
			one.push_back("MINU");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '*':
			position++;
			//out << "MULT *\n";
			one.push_back("22");
			one.push_back("*");
			one.push_back("MULT");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '/':
			position++;
			//out << "DIV /\n";
			one.push_back("23");
			one.push_back("/");
			one.push_back("DIV");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '<':
			position++;
			if (line[position] == '=') {
				position++;
				//out << "LEQ <=\n";
				one.push_back("25");
				one.push_back("<=");
				one.push_back("LEQ");
				one.push_back(std::to_string(linenum));
				composition.push_back(one);
			}
			else {
				//out << "LSS <\n";
				one.push_back("24");
				one.push_back("<");
				one.push_back("LSS");
				one.push_back(std::to_string(linenum));
				composition.push_back(one);
			}
			break;
		case '>':
			position++;
			if (line[position] == '=') {
				position++;
				//out << "GEQ >=\n";
				one.push_back("27");
				one.push_back(">=");
				one.push_back("GEQ");
				one.push_back(std::to_string(linenum));
				composition.push_back(one);
			}
			else {
				//out << "GRE >\n";
				one.push_back("26");
				one.push_back(">");
				one.push_back("GRE");
				one.push_back(std::to_string(linenum));
				composition.push_back(one);
			}
			break;
		case '!':
			position = position + 2;
			//out << "NEQ !=\n";
			one.push_back("29");
			one.push_back("!=");
			one.push_back("NEQ");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case ':':
			position++;
			//out << "COLON :\n";
			one.push_back("30");
			one.push_back(":");
			one.push_back("COLON");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '=':
			position++;
			if (line[position] == '=') {
				position++;
				//out << "EQL ==\n";
				one.push_back("28");
				one.push_back("==");
				one.push_back("EQL");
				one.push_back(std::to_string(linenum));
				composition.push_back(one);
			}
			else {
				//out << "ASSIGN =\n";
				one.push_back("31");
				one.push_back("=");
				one.push_back("ASSIGN");
				one.push_back(std::to_string(linenum));
				composition.push_back(one);
			}
			break;
		case ';':
			position++;
			//out << "SEMICN ;\n";
			one.push_back("32");
			one.push_back(";");
			one.push_back("SEMICN");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case ',':
			position++;
			//out << "COMMA ,\n";
			one.push_back("33");
			one.push_back(",");
			one.push_back("COMMA");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '(':
			position++;
			//out << "LPARENT (\n";
			one.push_back("34");
			one.push_back("(");
			one.push_back("LPARENT");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case ')':
			position++;
			//out << "RPARENT )\n";
			one.push_back("35");
			one.push_back(")");
			one.push_back("RPARENT");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '[':
			position++;
			//out << "LBRACK [\n";
			one.push_back("36");
			one.push_back("[");
			one.push_back("LBRACK");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case ']':
			position++;
			//out << "RBRACK ]\n";
			one.push_back("37");
			one.push_back("]");
			one.push_back("RBRACK");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '{':
			position++;
			//out << "LBRACE {\n";
			one.push_back("38");
			one.push_back("{");
			one.push_back("LBRACE");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		case '}':
			position++;
			//out << "RBRACE }\n";
			one.push_back("39");
			one.push_back("}");
			one.push_back("RBRACE");
			one.push_back(std::to_string(linenum));
			composition.push_back(one);
			break;
		default:
			position++;
			break;
		}
	}
}

void charConError(string s) {
	char x = s[1];
	if (x == '+' || x == '-' || x=='*' || x=='/' || x=='_'||
		(x >= '0'&&x<='9') || (x>='a' && x<='z')) {
		//do nothing
	}
	else {
		vector<string>temp;
		temp.push_back(to_string(linenum));
		temp.push_back("a");
		errorList.push_back(temp);
		//error << linenum << " a\n";
	}
}

void stringError(string temp) {
	int x = temp.size();
	if (x == 2) {
		vector<string>temp;
		temp.push_back(to_string(linenum));
		temp.push_back("a");
		errorList.push_back(temp);
		//error << linenum << " a\n";
		return;
	}
	for (int i = 1; i < x-1; i++) {
		int ascll  = (int)temp[i];
		if (ascll == 32 || ascll == 33 || (ascll >= 35 && ascll <= 126)) {
			//right
		}
		else {
			vector<string>temp;
			temp.push_back(to_string(linenum));
			temp.push_back("a");
			errorList.push_back(temp);
			//error << linenum << " a\n";
			return;
		}
	}
}

void dealMatch(string temp, string s) {
	vector<string> one;
	if (temp[0] == '\'') {
		//out << "CHARCON " << temp[1] << "\n";
		charConError(s);
		one.push_back("3");
		one.push_back(temp.substr(1, temp.size() - 2));
		one.push_back("CHARCON");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (temp[0] == '\"') {
		//out << "STRCON " << temp.substr(1, temp.size() - 2) << "\n";
		stringError(temp);
		one.push_back("4");
		one.push_back(temp.substr(1, temp.size() - 2));
		one.push_back("STRCON");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (temp[0] >= '0' && temp[0] <= '9') {
		//out << "INTCON " << temp << "\n";
		one.push_back("2");
		one.push_back(temp);
		one.push_back("INTCON");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("const") == 0) {
		//out << "CONSTTK " << temp << "\n";
		one.push_back("5");
		one.push_back(temp);
		one.push_back("CONSTTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("int") == 0) {
		//out << "INTTK " << temp << "\n";
		one.push_back("6");
		one.push_back(temp);
		one.push_back("INTTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("char") == 0) {
		//out << "CHARTK " << temp << "\n";
		one.push_back("7");
		one.push_back(temp);
		one.push_back("CHARTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("void") == 0) {
		//out << "VOIDTK " << temp << "\n";
		one.push_back("8");
		one.push_back(temp);
		one.push_back("VOIDTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("main") == 0) {
		//out << "MAINTK " << temp << "\n";
		one.push_back("9");
		one.push_back(temp);
		one.push_back("MAINTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("if") == 0) {
		//out << "IFTK " << temp << "\n";
		one.push_back("10");
		one.push_back(temp);
		one.push_back("IFTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("else") == 0) {
		//out << "ELSETK " << temp << "\n";
		one.push_back("11");
		one.push_back(temp);
		one.push_back("ELSETK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("switch") == 0) {
		//out << "SWITCHTK " << temp << "\n";
		one.push_back("12");
		one.push_back(temp);
		one.push_back("SWITCHTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("case") == 0) {
		//out << "CASETK " << temp << "\n";
		one.push_back("13");
		one.push_back(temp);
		one.push_back("CASETK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("default") == 0) {
		//out << "DEFAULTTK " << temp << "\n";
		one.push_back("14");
		one.push_back(temp);
		one.push_back("DEFAULTTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("while") == 0) {
		//out << "WHILETK " << temp << "\n";
		one.push_back("15");
		one.push_back(temp);
		one.push_back("WHILETK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("for") == 0) {
		//out << "FORTK " << temp << "\n";
		one.push_back("16");
		one.push_back(temp);
		one.push_back("FORTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("scanf") == 0) {
		//out << "SCANFTK " << temp << "\n";
		one.push_back("17");
		one.push_back(temp);
		one.push_back("SCANFTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("printf") == 0) {
		//out << "PRINTFTK " << temp << "\n";
		one.push_back("18");
		one.push_back(temp);
		one.push_back("PRINTFTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else if (s.compare("return") == 0) {
		//out << "RETURNTK " << temp << "\n";
		one.push_back("19");
		one.push_back(temp);
		one.push_back("RETURNTK");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}
	else {
		//out << "IDENFR " << temp << "\n";
		one.push_back("1");
		one.push_back(temp);
		one.push_back("IDENFR");
		one.push_back(std::to_string(linenum));
		composition.push_back(one);
	}

}

void getsym() {
	regex pattern("[a-zA-Z_][a-zA-Z0-9_]*|\".*?\"|\'.\'|\\d+");
	string temp;
	smatch result;
	string::const_iterator iterStart = line.begin();
	string::const_iterator iterEnd = line.end();
	std::sregex_iterator iter(line.begin(), line.end(), pattern);
	std::sregex_iterator end;
	position = 0;
	while (iter != end) {
		int head = iter->position();
		temp = (*iter)[0];
		int tail = head + temp.size();
		//cout << head << " " << tail << " " << position << " "<<temp << "\n";
		dealOther(head);
		temp = (*iter)[0];
		string s = temp;
		std::transform(s.begin(), s.end(), s.begin(), ::tolower);
		position = tail;
		dealMatch(temp, s);
		++iter;
	}
	dealOther(line.size());
}

void lexical() {
	linenum = 1;
	while (getline(f, line)) {
		getsym();
		linenum++;
	}
	
}
