#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#pragma comment(lib,"ws2_32.lib")

DWORD WINAPI ThreadProc(LPVOID lpParameter)		//���̣߳�����Ϣ
{
	//����socket2
	SOCKET s2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//�����׽ӿ�
	sockaddr_in tcpaddr2;
	tcpaddr2.sin_family = AF_INET;
	tcpaddr2.sin_port = htons(5050);  //���Ͷ˿�5050
	tcpaddr2.sin_addr.S_un.S_addr = inet_addr("10.210.225.191");
	int len = sizeof(SOCKADDR);

	while (1)
	{
		printf("�ң�\n    ");
		char sendBuf[100] = "\0";
		scanf_s("%s", sendBuf);
		sendto(s2, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&tcpaddr2, len);
		Sleep(1000);
	}

	closesocket(s2);
	return 0;
}

int main(int argc, char* argv[])
{

	WORD wVersionRequested;
	WSADATA wsaData;

	int iSockErr, iSockErr2;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		printf("Winsock ��ʼ������\n");//Winsock��ʼ������
		system("pause");
	}
	if (wsaData.wVersion != wVersionRequested)
	{
		printf("Winsock �汾��ƥ�䣡\n");//Winsock�汾��ƥ��
		WSACleanup();
		system("pause");
	}

	//����socket
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//�����׽ӿ�
	sockaddr_in tcpaddr;
	tcpaddr.sin_family = AF_INET;
	tcpaddr.sin_port = htons(5050);  //���ն˿�5050
	tcpaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//���׽ӿ�
	if (bind(s, (LPSOCKADDR)&tcpaddr, sizeof(tcpaddr)) == SOCKET_ERROR)
	{
		iSockErr = WSAGetLastError();
		printf("%d", iSockErr);//���ݲ�ͬ�Ĵ������ͽ��в�ͬ�Ĵ���
		system("pause");
	}
	//������̣߳�����Ϣ
	HANDLE hThread;
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	CloseHandle(hThread);

	char recvBuf[50] = "\0";
	int len = sizeof(SOCKADDR);
	sockaddr_in addrClient;
	while (1)
	{
		recvfrom(s, recvBuf, 50, 0, (SOCKADDR*)&addrClient, &len);
		printf("����\n    %s\n", recvBuf);
		Sleep(1000);
	}
	closesocket(s);
	WSACleanup();
	return 0;
}