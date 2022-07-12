#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <conio.h>
#include <stack>
#include <map>
#include <vector>
#include <unordered_map>
#define digit 1 // 1����
#define op 2 // +-*/()#
#define Hh 3 // 3Hh
#define AF 4 // 4A-F
#define letter 5 // 5������ĸ
using namespace std;
const int N = 8;

typedef struct node {
	char data;
	struct node* before;
	struct node* next;
};

node* temp, * top;

char q; // ָ��������Ŵ��е�ǰ���ַ�
char word[20]; // �洢��ǰʶ��ĵ���
int state; // ��ʾ������״̬
int i; // ���ʵ��±�

// �洢�㷨���ȹ�ϵ��
// ���ڹ���Ϊ1�����ڹ�ϵΪ0��С�ڹ�ϵΪ-1������Ϊ9
// ˳��+, -, *, /, i, (, ), #
int table[N][N] = {
	{1, 1, -1, -1, -1, -1, 1, 1},
	{1, 1, -1, -1, -1, -1, 1, 1},
	{1, 1, 1, 1, -1, -1, 1, 1},
	{1, 1, 1, 1, -1, -1, 1, 1},
	{1, 1, 1, 1, 9, 9, 1, 1},
	{-1, -1, -1, -1, -1, -1, 0, 9},
	{1, 1, 1, 1, 9, 9, 1, 1},
	{-1, -1, -1, -1, -1, -1, 9, 0}
};

void push(char c); // ��ջ
char pop(); // ��ջ
int t2j(char current); // ���ַ����ֻ�
int parser(string line);
bool check_terminal(char ch); // �ж��Ƿ����ս��
int isDigitOrChar(char ch);
string change_i(string words); // ������ʮ���ƻ�ʮ���������ı��ʽת��Ϊ��i����ı��ʽ


int main() {
	top = (node*)malloc(sizeof(node));
	top->before = NULL;
	top->next = NULL;
	top->data = ' ';
	string line = "i+(i+i*i#";
	
	cout << "Start parse string " << line << ":" << endl << endl;
	parser(line);

	return 0;
}

void push(char c) {  // ��ջ����
	temp = (node*)malloc(sizeof(node));
	
	temp->data = c;
	temp->before = top;
	temp->next = NULL;

	top->next = temp;  // ˫������
	top = temp;
}

char pop() {
	char ch = top->data;

	if (top->before != NULL) {
		temp = top;
		top = temp->before;
		temp->before = NULL;
		top->next = NULL;
		free(temp);
	}
	
	return ch;
}

int t2j(char current) {
	// ˳��+, -, *, /, i, (, ), #
	int j = 0;

	switch (current) {
	case '+': j = 0; break;
	case '-': j = 1; break;
	case '*': j = 2; break;
	case '/': j = 3; break;
	case 'i': j = 4; break;
	case '(': j = 5; break;
	case ')': j = 6; break;
	case '#': j = 7;
	}

	return j;
}

void showMess(int l, string line) {
	
	node* t = top;
	//cout << t->data;
	vector<char> v;
	while (t) {
		v.push_back(t->data);
		//cout << t->data;
		t = t->before;
		
	}

	string str;
	for (int i = v.size()-1; i >= 0; i--) {
		str += v[i];
	}
	cout << str;

	cout << "\t\t";
	for (int i = l; i < line.size(); i++) {
		cout << line[i];
	}
	cout << "\t\t";

}

int parser(string line) {
	int i, j;
	push('#');
	
	int k = 1;

	bool flag = true;
	// line[l] != '#'
	for (int l = 0; ; l++) {
		showMess(l, line);

		// �˳�����
		if (top->data == 'N' && top->before->data == '#' && line[l] == '#') break;

		node* sktemp = top;
		char sk = top->data;
		char a = line[l];
		//cout << a << endl;
		// �κ����ս��֮�����ֻ��һ���ս���������ս����ǰѰ��һλ����
		if (!check_terminal(sk)) {
			sk = top->before->data;
			sktemp = top->before;
		}
		i = t2j(sk); // ��ȡջ���ս��
		j = t2j(a); // ��ȡ��ǰ�������
		//if (a == '+')
		//cout << i << ' ' << j << endl;
		switch (table[i][j]) {
		case 9:  // �﷨����
			flag = false;
			break;
		case 0: 
			cout << "=" << "\t\t" << "push in" << endl;
			push(a);
			break;
		case -1:  // С�ڣ��ƽ�
			cout << "<" << "\t\t" << "push in" << endl;
			//cout << a << endl;
			push(a);
			break;
		case 1:   // ���ڣ���Լ
			cout << ">" << "\t\t" << "reduce" << endl;
			node * Q = sktemp;
			do {
				if (check_terminal(Q->before->data)) Q = Q->before;
				else Q = Q->before->before;
			} while (table[t2j(Q->data)][i] == 0);
			//Q++;
			while (top != Q) {
				char c = pop();
			}
			push('N');
			l--;

			break;
		}
		if (!flag) break;
	}

	if (!flag) {
		cout << endl << line << " is not valid." << endl;
	}
	else {
		cout << endl << line << " is valid." << endl;
	}

	return 1;
}

int isDigitOrChar(char ch) {
	if (ch >= 48 && ch <= 57) // ����
		return digit;
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
			case op: // ������
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

// �ж��Ƿ����ս��
bool check_terminal(char ch) {
	if (isDigitOrChar(ch) == op || ch == 'i') return true;
	else return false;
}