/*
    Designed for Udemy OS course
	Builds a server socket that:
		- listens on a socket
		- sends a web-page whenever a client connects to the sockets
	Alternative server program to "sockets_win1_srvr.c"
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <winsock2.h>

#pragma comment(lib,"Ws2_32.lib")

int main() {
	// Initialize WinSock
	WSADATA wsa;
	int startup = WSAStartup(MAKEWORD(2,2),&wsa);
	if(startup != 0) {printf("Error initializing WinSock: %d\n",WSAGetLastError());}

	// Prepare response msg
	FILE* body_file;
	body_file = fopen("index.html","r");
	char http_body[1024];
	fgets(http_body,sizeof(http_body),body_file);

	char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
	strcat(http_header,http_body);

	// Create socket
	SOCKET srvr_sock;
	srvr_sock = socket(AF_INET,SOCK_STREAM,0);

	// Generate srvr addr
	struct sockaddr_in srvr_addr;
	srvr_addr.sin_family = AF_INET;
	srvr_addr.sin_port = htons(8001);
	srvr_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind
	int bound = bind(srvr_sock,(struct sockaddr*)&srvr_addr,sizeof(srvr_addr));
	if(bound != 0) {printf("Error binding server socket: %d\n",WSAGetLastError());}

	// Listen
	int listened = listen(srvr_sock,5);
	if(listened != 0) {printf("Error listening on server socket: %d\n",WSAGetLastError());}

	// Accept
	SOCKET cli_sock;
	char buf[2048];

	while(1) {
		cli_sock = accept(srvr_sock,NULL,NULL);

		// Send msg
		if(send(cli_sock,http_header,sizeof(http_header),0) == SOCKET_ERROR) {
			printf("Error sending message: %d\n",WSAGetLastError());
		}

		shutdown(cli_sock, 1);

		/*
		while(recv(cli_sock,buf,sizeof(buf),0) != 0) {
			sleep(5);
		}*/

		if(closesocket(cli_sock) != 0) {
			printf("Error closing socket: %d\n",WSAGetLastError());
		}
	}

	closesocket(srvr_sock);
	system("pause");
	return 0;
}
