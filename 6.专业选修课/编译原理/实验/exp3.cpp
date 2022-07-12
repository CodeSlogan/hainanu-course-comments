#include <iostream>
#include <string>
#include <cstring>
#define digit 1 // 1����
#define op 2 // +-*/()#
#define Hh 3 // 3Hh
#define AF 4 // 4A-F
#define letter 5 // 5������ĸ
using namespace std;

typedef struct node {
	char data;
	struct node* next;
};
node* p, * h, * temp, * top, * base;
char cmpchar;
string line;
// ���������ṹ
int table[5][8] = {
	{0, 0, 0, 0, 1, 0, 1, 0},
	{1, 1, 0, 0, 0, 1, 0, 1},
	{0, 0, 0, 0, 1, 0, 1, 0},
	{1 ,1, 1, 1, 0, 1, 0, 1},
	{0, 0, 0, 0, 1, 0, 1, 0}
};

char q; // ָ��������Ŵ��е�ǰ���ַ�
char word[20]; // �洢��ǰʶ��ĵ���
int state; // ��ʾ������״̬
int i; // ���ʵ��±�

char read(string line, int k);
void push(char c);
void pop();
int i2d(char cmpchar); // EATBF
int j2d(char current); // +-*/()i#
void dopush(int t);
int isDigitOrChar(char ch);
bool check_terminal(char ch); // �ж��Ƿ����ս��
string change_i(string words); // ������ʮ���ƻ�ʮ���������ı��ʽת��Ϊ��i����ı��ʽ


int main() {
	cout << "Please input the string which is at the end of #:" << endl;
	getline(cin, line);
	//cout << line << endl;

	int i, j, t;

	push('#');
	push('E'); // ��ʼ��
	int cur = 0;
	char current; 

	while (cur < line.size()) {
		current = read(line, cur);
		cmpchar = top->data;
		pop();
		printf("Top: %c --- Cur: %c", cmpchar, current);
		// ջ�����ս����#�������봮�в����ս����#ʱ���ж�Ϊ����
		if (check_terminal(cmpchar) && cmpchar != current) {
			cur--; // �����ж�Ϊ�Ƿ�
			break;
		}

		if (current == cmpchar) {
			if (current == '#') break;
			printf("	match success of %c\n\n", current);
			cur++;
			continue;
		}
		cout << endl;
		i = i2d(cmpchar);
		j = j2d(current);
		if (table[i][j] == 1) {
			t = 10 * i + j;
			dopush(t);
		}
		else {
			cur--; // �����ж�Ϊ�Ƿ�
			break;
		}
	}

	if (cur + 1 == line.size()) {
		cout << endl << "Your input is valid!" << endl;
	}
	else {
		cout << endl << "Sorry, your input is invalid!" << endl;
	}

	return 0;
}

char read(string line, int k) {
	return line[k];
}

// ѹջ
void push(char c) {
	temp = (node*)malloc(sizeof node);
	temp->data = c;
	temp->next = top;
	top = temp;
}

// ��ջ
void pop() {
	cmpchar = top->data;

	if (top->next != NULL)
		top = top->next;
}

// ��i�ַ����ֻ�
int i2d(char cmpchar) {
	int i = 0;

	switch (cmpchar) {
	case 'E': i = 0; break;
	case 'A': i = 1; break;
	case 'T': i = 2; break;
	case 'B': i = 3; break;
	case 'F': i = 4;
	}

	return i;
}

// ��j�ַ����ֻ�
int j2d(char current) {
	int j = 0;

	switch (current) {
	case '+': j = 0; break;
	case '-': j = 1; break;
	case '*': j = 2; break;
	case '/': j = 3; break;
	case '(': j = 4; break;
	case ')': j = 5; break;
	case 'i': j = 6; break;
	case '#': j = 7; 
	}

	return j;
}

void dopush(int t) {
	switch (t) {
	case 4: push('A'); push('T'); break;
	case 6: push('A'); push('T'); break;
	case 10: push('A'); push('T'); push('+'); break;
	case 11: push('A'); push('T'); push('-'); break;
	case 15: break;
	case 17: break;
	case 24: push('B'); push('F'); break;
	case 26: push('B'); push('F'); break;
	case 30: break;
	case 31: break;
	case 32: push('B'); push('F'); push('*'); break;
	case 33: push('B'); push('F'); push('/'); break;
	case 35: break;
	case 37: break;
	case 44: push(')'); push('E'); push('('); break;
	case 46: push('i'); break;
	}
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