/*
	���Կո���ַ����з��������
*/ 
#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdio>
#include <cstring>
using namespace std;

char words[200] = "  Ae35 6638 5392H A10 83A2Eh 65Ha 3G2H 80  ";
char* q; // ָ��������Ŵ��е�ǰ���ַ�
char word[20]; // �洢��ǰʶ��ĵ���
int state = 0; // ��ʾ������״̬
int i; // ���ʵ��±�

int main() {
	printf("%s \n", words);

	q = words;
	i = 0;
	memset(word, 0, sizeof word);

	while (*q) {
		if (*q == 32) {
			if (i > 0) {
				word[i] = '\0';
				printf("%s ", word);
			}
			i = 0;
			memset(word, 0, sizeof word);
		} else {
			word[i++] = *q;
		}
		q++;
	}


	return 0;
}