/*
    Designed for Udemy OS course
	Builds a server socket that:
		- listens on a socket
		- sends a message whenever a client connects to the sockets
*/

#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

//#pragma comment(lib,"ws2_32.lib")

int main() {
	//Initialize WinSock
	WSADATA wsa;
	int startup = WSAStartup(MAKEWORD(2,2),&wsa);
	if(startup != 0) {printf("Error starting WinSock");}

	// Message to send
	char srvr_msg[256] = "Hi there, this is the server speaking.";

	// Create socket
	SOCKET srvr_sock;
	srvr_sock = socket(AF_INET,SOCK_STREAM,0);

	// Create srvr addr
	struct sockaddr_in srvr_addr;
	srvr_addr.sin_family = AF_INET;
	srvr_addr.sin_port = htons(9002);
	srvr_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr("0.0.0.0");

	// Bind
	int bound = bind(srvr_sock,(struct sockaddr*)&srvr_addr,sizeof(srvr_addr));
	if(bound != 0) {printf("Error binding server socket: %d\n",WSAGetLastError());}

	// Listen
	int listened = listen(srvr_sock,5);
	if(listened != 0) {printf("Error listening\n");}

	// Accept
	SOCKET cli_sock;
	cli_sock = accept(srvr_sock,NULL,NULL);

	// Send msg
	if(send(cli_sock,srvr_msg,sizeof(srvr_msg),0) == SOCKET_ERROR) {
		printf("Error sending message: %d", WSAGetLastError());
	}

	close(srvr_sock);
	system("pause");
	return 0;
}
