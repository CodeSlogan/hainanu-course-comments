#include <iostream>
#include <cstring>
#include <string>
#include <conio.h>
#include <cstdio>
#define digit 1 // 1����
#define space 2 // 2�ո�
#define Hh 3 // 3Hh
#define AF 4 // 4A-F
#define letter 5 //5������ĸ
using namespace std;

string words;
char q; // ָ��������Ŵ��е�ǰ���ַ�
char word[20]; // �洢��ǰʶ��ĵ���
int state = 0; // ��ʾ������״̬
int i; // ���ʵ��±�

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
}

int main() {
	// = "  Ae35 6638 5392H A10 83A2Eh 65Ha 3G2H 80  #"
	cout << "�������ʶ���������Կո�ָ�(#��β)��" << endl;
	getline(cin, words);

	cout << "Input string is: " << words << endl;

	int cnt = 0;
	q = words[cnt++];

	while (q != '#') {
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
			case space: // �ո�
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
			case space: // ������ϣ�ʶ��Ϊ��ʶ��
				word[i] = '\0';
				printf("%s is an identifier.\n", word);
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
			case space: // �ɹ�ʶ��Ϊ����
				word[i] = '\0';
				printf("%s is an Integer.\n", word);
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
			case space: // ʶ��Ϊ16������
				word[i] = '\0';
				printf("%s is a Hex digit.\n", word);
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
			default:
				word[i++] = q;
				state = 5;
			}
			break;
		case 5: // ����״̬
			if (q == 32) { // ��Ϊ�ո���ʶ��Ϊ�Ǳ�ʶ��
				word[i] = '\0';
				printf("%s is not an identifier.\n", word);
				memset(word, 0, sizeof word);
				i = 0;
				state = 0;
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

	return 0;
}