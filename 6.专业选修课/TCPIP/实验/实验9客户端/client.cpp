#include <stdio.h>
#include <WinSock2.h> //windows socket��ͷ�ļ�
#include <Windows.h>
#include <iostream>
#include <thread>
#include <process.h>
#pragma comment(lib, "ws2_32.lib") //����winsock2.h�ľ�̬���ļ�
using namespace std;


int main()
{
	//����winsock��
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 3), &wsadata);

	//�ͻ���socket
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, 0);

	//��ʼ��socket��Ϣ
	//memset:��������һ���ڴ�������ĳ��������ֵ�����Խϴ�Ľṹ�������������������һ����췽����
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(SOCKADDR));

	//����Socket�����ӵ�ַ����ʽ�Ͷ˿�
	clientAddr.sin_addr.s_addr = inet_addr("192.168.43.68");
	clientAddr.sin_family = PF_INET;
	clientAddr.sin_port = htons(2017);

	//��������
	connect(clientSock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));
	cout << "�ѽ������ӡ�" << endl;

	//������Ϣ
	char* s = new char[100];
	cout << "��������Ҫ���͵�������Ϣ: ";
	cin >> s;
	send(clientSock, s, strlen(s) * sizeof(char) + 1, NULL);
	cout << "�ѷ���:" << s << endl;

	//������Ϣ
	system("pause");
	char Buffer[MAXBYTE] = { 0 };
	recv(clientSock, Buffer, MAXBYTE, 0);
	cout << "ͨ���˿�:" << ntohs(clientAddr.sin_port) << "���յ�:" << Buffer << endl;

	//�ر�����
	closesocket(clientSock);
	WSACleanup();
	cout << "�ͻ��������ѹرա�" << endl;

	system("pause");
	return 0;
}
