#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll
using namespace std;
int main() {
	char n[100];
	
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	
	//��ͻ��˷�������
	while (1) {
		cin >> n;
		char *img = n;
		char* image_f = img;
		const char* str = n;
		send(sock, str, strlen(str) + sizeof(char), NULL);
		//���շ��������ص�����
		char szBuffer[MAXBYTE] = { 0 };
		recv(sock, szBuffer, MAXBYTE, NULL);
		//������յ�������
		printf("Message from server: %s\n", szBuffer);
	}
	//�ر��׽���
	closesocket(sock);
	//��ֹʹ�� DLL
	WSACleanup();
	system("pause");
	return 0;
}