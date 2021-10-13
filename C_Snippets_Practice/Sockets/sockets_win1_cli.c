/*
    Designed for Udemy OS course
	Builds a client socket that:
		- connects to a local server
		- prints the response message
*/

#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

int main() {
	// Initialize WinSock
	WSADATA wsa;
	int startup = WSAStartup(MAKEWORD(2,2),&wsa);
	if(startup != 0) {printf("Error starting up WinSock");}

	//Create socket
	SOCKET cli_sock;
	cli_sock = socket(AF_INET,SOCK_STREAM,0);

	// Set server addr
	struct sockaddr_in srvr_addr;
	srvr_addr.sin_family = AF_INET;
	srvr_addr.sin_port = htons(9002);
	srvr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Connect
	int connected = connect(cli_sock,(struct sockaddr*)&srvr_addr,sizeof(srvr_addr));
	if(connected != 0) {printf("Error connecting: %d\n", WSAGetLastError());}

	// Receive msg
	char srvr_msg[256];
	recv(cli_sock,srvr_msg,sizeof(srvr_msg),0);

	printf("Message sent by server: %s\n\n",srvr_msg);

	close(cli_sock);
	system("pause");
	return 0;
}
