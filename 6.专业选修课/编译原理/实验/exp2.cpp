#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <conio.h>
#define digit 1 // 1����
#define space 2 // 2�ո�
#define Hh 3 // 3Hh
#define AF 4 // 4A-F
#define letter 5 //5������ĸ
#define op 6
using namespace std;

char sym; // ���浱ǰ�����ַ� 
string line; // ��������һ�б��ʽ
int cur; // ���ʽ�ַ����еĵ�ǰ�±�
int error; // �����־��0����ȷ�� -1������
char q; // ָ��������Ŵ��е�ǰ���ַ�
char word[20]; // �洢��ǰʶ��ĵ���
int state; // ��ʾ������״̬
int i; // ���ʵ��±�

int E(), E1(), E2(), T(), T1(), T2(), F(); // ��������
char read(string line, int k);
string change_i(string words); // ������ʮ���ƻ�ʮ���������ı��ʽת��Ϊ��i����ı��ʽ
int isDigitOrChar(char ch);

int main() {
	ifstream fin("D:/Compile_exp/exp2-test.txt");
	if (!fin.is_open()) {
		cout << "open file error." << endl;
		_getch();
		return -1;
	}

	while (getline(fin, line)) {
		puts("------------------------------------");
		cur = 0;
		error = 0;
		string temp = line;
		line = change_i(line);
		if (line == "-1") {
			cout << temp << " is not a valid express." << endl;
			continue;
		}
		cout << "Output string is: " << line << endl;

		sym = read(line, cur); // ��ȡ��һ���ַ�
		E();

		if (error == -1)
			cout << temp << " is not valid." << endl;
		else if (error == 0)
			cout << temp << " is valid." << endl;
	}

	fin.close();
	_getch();

	return 0;
}

// �ݹ��������ʵ��
int E() {
	T();
	E1();
	E2();

	return 0;
}

int E1() {
	if (sym == '+') {
		cur++;
		sym = read(line, cur);
		T();
		E1();
	}
	else if (sym == '#' || sym == ')' || sym == '-')
		return 0;
	else
		error = -1;

	return 0;
}

int E2() {
	if (sym == '-') {
		cur++;
		sym = read(line, cur);
		T();
		E2();
	}
	else if (sym == '#' || sym == ')')
		return 0;
	else
		error = -1;

	return 0;
}

int T() {
	F();
	T1();
	T2();

	return 0;
}

int T1() {
	if (sym == '*') {
		cur++;
		sym = read(line, cur);
		F();
		T1();
	}
	else {
		if (sym == '#' || sym == ')' || sym == '+' || sym == '-' || sym == '/')
			return 0;
		else
			error = -1;
	}
	return 0;
}

int T2() {
	if (sym == '/') {
		cur++;
		sym = read(line, cur);
		F();
		T2();
	}
	else {
		if (sym == '#' || sym == ')' || sym == '+' || sym == '-')
			return 0;
		else
			error = -1;
	}
	return 0;
}

int F() {
	if (sym == 'i') {
		cur++;
		sym = read(line, cur);
	}
	else if (sym == '(') {
		cur++;
		sym = read(line, cur);
		E();
		if (sym == ')') {
			cur++;
			sym = read(line, cur);
		}
		else
			error = -1;
	}
	else
		error = -1;

	return 0;
}

char read(string line, int k) {
	return line[k];
}

int isDigitOrChar(char ch) {
	if (ch >= 48 && ch <= 57) // ����
		return digit;
	else if (ch == 32) // �ո� 
		return space;
	else if (ch == 72 || ch == 104) // H or h
		return Hh;
	else if ((ch >= 65 && ch <= 70) || (ch >= 97 && ch <= 102)) // ��ĸA,B,C,D,E,F
		return AF;
	else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) // ��A~F���������ĸ
		return letter;
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#')
		return op;
}

// ������ʮ���ƻ�ʮ���������ı��ʽת��Ϊ��i����ı��ʽ
string change_i(string words) {
	memset(word, 0, sizeof word);
	state = 0;
	i = 0;
	cout << "Input string is: " << words << endl;

	string result = "";
	int cnt = 0;
	q = words[cnt++];

	while (cnt <= words.size()) {
		// ���ж�״̬�����ж��ַ�
		switch (state) {
		case 0: // 0״̬
			//puts("״̬0");
			switch (isDigitOrChar(q)) {
			case digit: // ����
				word[i++] = q;
				state = 2; // ת�Ƶ�2״̬
				break;
			case Hh: // H or h
			case AF: // ��ĸA,B,C,D,E,F or a,b,c,d,e,f
			case letter: // ��ĸ
				word[i++] = q;
				state = 1;
				break;
			case op: // �ո�
				result += q;
				state = 0;
				break;
			default: // �������Ƿ��ַ� ��
				word[i++] = q;
				state = 5;
			}
			break;
		case 1: // 1״̬
			switch (isDigitOrChar(q)) {
			case Hh: // ��ǰ״̬������ĸ���������¶���
			case AF:
			case digit:
			case letter:
				word[i++] = q;
				state = 1;
				break;
			case op: // ������ϣ�ʶ��Ϊ��ʶ��
				word[i] = '\0';
				printf("%s is an identifier.\n", word);
				//result += "i";
				memset(word, 0, sizeof word);
				i = 0;
				state = 0;
				result = "-1";
				return result;
				break;
			default:
				word[i++] = q;
				state = 5;
			}
			break;
		case 2: // 2״̬
			//puts("״̬2");
			//printf("%s\n", word);
			switch (isDigitOrChar(q)) {
			case digit: // ��Ϊ���֣����ı�״̬���¶���
				word[i++] = q;
				state = 2;
				break;
			case Hh: // ��ΪHh��ת����״̬3
				word[i++] = q;
				state = 3;
				break;
			case AF: // ��ΪAF�����п�����16���ƣ�ת����״̬4
				word[i++] = q;
				state = 4;
				break;
			case op: // �ɹ�ʶ��Ϊ����
				word[i] = '\0';
				printf("%s is an Integer.\n", word);
				result += "i";
				result += q;
				//cout << result << endl;
				memset(word, 0, sizeof word);
				i = 0;
				state = 0;
				break;
			default:
				word[i++] = q;
				//printf("%s\n", word);
				state = 5;
			}
			break;
		case 3: // 3״̬
			switch (isDigitOrChar(q)) {	
			case op: // ʶ��Ϊ16������
				word[i] = '\0';
				printf("%s is a Hex digit.\n", word);
				result += "i";
				result += q;
				//cout << result << endl;
				memset(word, 0, sizeof word);
				i = 0;
				state = 0;
				break;
			default:
				word[i++] = q;
				state = 5;
			}
			break;
		case 4: // 4״̬
			//puts("��ǰ״̬Ϊ4");
			switch (isDigitOrChar(q)) {
				
			case digit: // ��Ϊ���ֻ�A~F����Ϊ״̬4�����¶���
			case AF:
				word[i++] = q;
				state = 4;
				break;
			case Hh:
				word[i++] = q;
				state = 3;
				break;
			case op: // ���16����û����h��H��β��ת��������״̬
				state = 5;
				cnt--;
				break;
			default:
				word[i++] = q;
				state = 5;
			}
			break;
		case 5: // ����״̬
			//puts("״̬5");
			//printf("%s\n", word);
			if (isDigitOrChar(q) == op) { // ��Ϊ�ո���ʶ��Ϊ�Ǳ�ʶ��
				word[i] = '\0';
				printf("%s is not an identifier.\n", word);
				memset(word, 0, sizeof word);
				i = 0;
				state = 0;
				result = "-1";
				return result;
			}
			else { // �������л�δ��ȡ��ϣ����¶���
				word[i++] = q;
				q = words[cnt++];
				continue;
			}
			break;
		}
		q = words[cnt++]; // ָ�����ƣ�ָ��������Ŵ��е���һ���ַ���
	}
	
	return result;
}