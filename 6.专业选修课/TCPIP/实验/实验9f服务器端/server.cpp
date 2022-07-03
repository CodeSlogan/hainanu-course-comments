#include <stdio.h>
#include <WinSock2.h> //windows socket��ͷ�ļ�
#include <Windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <process.h>
#pragma comment(lib, "ws2_32.lib") //����winsock2.h�ľ�̬���ļ�
using namespace std;

//mutex ÿ���߳��ڶ���Դ����ǰ�������ȼ������ɹ��������ܲ�������������������
//ͬһʱ�̣�ֻ����һ���̳߳��и�����
mutex m;

//����ṹ����������
typedef struct my_file
{
	SOCKET clientSocket; //�ļ��ڲ�������һ��SOCKET ���ںͿͻ��˽���ͨ��
	sockaddr_in clientAddr; //���ڱ���ͻ��˵�socket��ַ
	int id; //�ļ�������
}F;

DWORD WINAPI transmmit(const LPVOID arg)
{
	//ʵ��������Ϊ��׷�󲢷��Բ�Ӧ�ü�����������Ϊ�˷��㿴���
	m.lock();

	F* temp = (F*)arg;
	//��ȡ�ļ������
	//int file_id = temp->id;
	//��ȡ�ͻ����Ķ˿ں�
	//ntohs(temp -> clientAddr.sin_port); 
	cout << "���Կ�ʼ,�ȴ��ͻ��˷�����Ϣ..." << endl;
	//�ӿͻ��˴���������
	char Buffer[MAXBYTE] = { 0 }; //������
	recv(temp->clientSocket, Buffer, MAXBYTE, 0); //recv���� �ӿͻ���ͨ��clientScocket����
	cout << "�߳�" << temp->id << "�ӿͻ��˵�" << ntohs(temp->clientAddr.sin_port) << "�Ŷ˿��յ�:" << Buffer << endl;

	//���ͼ򵥵��ַ������ͻ���
	const char* s = "Server file";
	send(temp->clientSocket, s, strlen(s) * sizeof(char) + 1, NULL);
	cout << "�߳�" << temp->id << "ͨ���ͻ��˵�" << ntohs(temp->clientAddr.sin_port) << "�Ŷ˿ڷ���:" << s << endl;

	m.unlock();

	return 0;
}

int main()
{
	//����winsock��,��һ��������winsocket load�İ汾�ţ�2.3��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 3), &wsaData);

	//�����������˵�socket��Э���壬 sokcet���ͣ�
	SOCKET servSocket = socket(AF_INET, SOCK_STREAM, 0);//����ĳ�SOCK_DGRAM��ʹ��UDP

	// ��ʼ��socket��Ϣ
	sockaddr_in servAddr; //��������socket��ַ������sin_addr��ʾIP��ַ��sin_port���ֶ˿ںź�sin_zero����ֽ�
	memset(&servAddr, 0, sizeof(SOCKADDR)); //��ʼ��socket��ַ

	//����Socket�����ӵ�ַ����ʽ�Ͷ˿ڣ�����
	servAddr.sin_family = PF_INET; //����ʹ�õ�Э����
	servAddr.sin_port = htons(2017); //����ʹ�õĶ˿�
	servAddr.sin_addr.s_addr = inet_addr("192.168.43.68"); //���ð󶨵�IP��ַ
	::bind(servSocket, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)); //��֮ǰ������servSocket�Ͷ˿ڣ�IP��ַ��

	HANDLE hThread[20]; //��ȡ���
	listen(servSocket, 20); //�����������˿ڣ����20������
	for (int i = 0; i < 20; i++)
	{
		F* temp = new F; //�����µĴ���ṹ��
		sockaddr_in clntAddr;
		int nSize = sizeof(SOCKADDR);
		SOCKET clientSock = accept(servSocket, (SOCKADDR*)&clntAddr, &nSize);
		//temp���ݳ�Ա��ֵ
		temp->clientSocket = clientSock;
		temp->id = i + 1;
		temp->clientAddr = clntAddr;
		//ͨ������������߳�
		hThread[i] = CreateThread(NULL, 0, &transmmit, temp, 0, NULL);
	}

	//�ȴ����߳����
	WaitForMultipleObjects(20, hThread, TRUE, INFINITE);
	cout << WSAGetLastError() << endl; //�鿴������Ϣ

	//�ر�socket���ͷ�winsock
	closesocket(servSocket);
	WSACleanup();

	cout << "�����������ѹرա�" << endl;
	system("pause");

	return 0;
}
