#include "Winsock2.h""
#include "stdio.h"
#include "string.h"
#pragma comment(lib, "wsock32.lib")

#define RECV_PORT 3001
#define SEND_PORT 3000

SOCKET sock;
sockaddr_in ServerAddr;
sockaddr_in ClientAddr;

void main()
{
	int n;
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		printf("�׽��ֳ�ʼ��ʧ��!\n");
		return;
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == SOCKET_ERROR)
	{
		printf("�׽��ִ����ɹ�!\n");
		WSACleanup();
		return;
	}

	memset(&ClientAddr, 0, sizeof(ClientAddr));
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_addr.s_addr = inet_addr("10.210.225.191");
	ClientAddr.sin_port = htons(RECV_PORT);

	n = bind(sock, (struct sockaddr*)&ClientAddr, sizeof(ClientAddr));
	if (n == SOCKET_ERROR)
	{
		printf("��ʧ��!\n");
		return;
	}
	else
	{
		printf("�󶨳ɹ�!\n");
	}

	char buf[1024] = "\0";
	int len;
	printf("��ʼ��������...\n");
	while (1)
	{
		memset(&buf, '\0', sizeof(buf));
		memset(&ServerAddr, 0, sizeof(ServerAddr)); 
		len = sizeof(ServerAddr);
		

		n = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&ServerAddr, (int *)&len);

		
		if (n == SOCKET_ERROR)
		{
			printf("\n ��ȡ�㲥����ʧ��! \n'");
			printf("\n �������: %d\n", WSAGetLastError());
		}
		
		else
		{
			printf("\n ��ȡ�㲥����: \" % s\" ���� %s \n", buf, inet_ntoa(ServerAddr.sin_addr));
			if (strcmp(buf, "/nane") >= 0)
			{
				ServerAddr.sin_family = AF_INET;
				ServerAddr.sin_addr.s_addr = inet_addr("10.210.225.191");
				ServerAddr.sin_port = htons(SEND_PORT);

				memset(&buf, '\0', sizeof(buf));
				strcpy(buf, "20181685310031 ����");
				n = sendto(sock, buf, strlen(buf) + 1, 0, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr));

				if (n == SOCKET_ERROR)
				{
					printf("����ʧ��!\n");
				}
				else if (n = 0)
				{
					printf("����ʧ��!\0");
				}
				else if (n != SOCKET_ERROR)
				{
					printf("���ͳɹ�!\n");
				}
			}
		}
		Sleep(1000);
	}
	getchar();
	closesocket(sock);
	WSACleanup();
}