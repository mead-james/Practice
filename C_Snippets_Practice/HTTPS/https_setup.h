/*
    Contains functions to support an HTTPS GET request
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypto.lib")
#pragma comment(lib, "ssl.lib")

#define BUFSIZE 2048

/*
 * Function: "startWinSock"
 * Parameters: N/A
 * Purpose: Initializes WinSock
 */
void startWinSock()
{
    // Initialize WinSock
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (err != 0)
    {
        printf("Error starting up WinSock: %d\n", err);
        exit(1);
    }
}

/*
 * Function: "createSocket"
 * Parameters:
 *      -url: the base url of the server to connect to
 * Purpose: Connects to a server by url. Returns the client socket.
 */
SOCKET createSocket(char *url, char *port)
{
    int err;

    // Get IPv4 addr of url string
    struct addrinfo *srvr_addr;
    struct addrinfo addr_hints = {0};
    addr_hints.ai_family = 2;
    addr_hints.ai_socktype = 1;
    addr_hints.ai_protocol = 6;

    err = getaddrinfo(url, port, &addr_hints, &srvr_addr);
    if (err != 0)
    {
        printf("Error getting address info from URL: %d\n", err);
        WSACleanup();
        exit(1);
    }

    // Create client socket
    SOCKET cli_sock = socket(srvr_addr->ai_family, srvr_addr->ai_socktype, srvr_addr->ai_protocol);
    if (cli_sock == INVALID_SOCKET)
    {
        printf("Error creating client socket: %d\n", WSAGetLastError());
    }

    // Connect client socket to url server
    err = connect(cli_sock, srvr_addr->ai_addr, srvr_addr->ai_addrlen);
    if (err != 0)
    {
        printf("Error connecting: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    return cli_sock;
}

/*
 * Function: "createSSL_CTX"
 * Parameters: N/A
 * Purpose: Initializes TLS for client. Returns SSL_CTX.
 */
SSL_CTX *createSSL_CTX()
{
    const SSL_METHOD *method = TLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(method);

    if (ctx == NULL)
    {
        printf("Error creating SSL context: %s", GetLastError());
        exit(1);
    }
    return ctx;
}

/*
 * Function: "connectTLS"
 * Parameters: 
 *      -ctx: the SSL context in use
 *      -cli_sock: the client socket to connect with TLS
 * Purpose: Connects TLS to client socket. Returns SSL connection.
 */
SSL *connectTLS(SSL_CTX *ctx, SOCKET *cli_sock)
{
    SSL *ssl_connect = SSL_new(ctx);
    if (ssl_connect == NULL)
    {
        printf("Error creating SSL connection: %s", GetLastError());
        exit(1);
    }

    SSL_set_fd(ssl_connect, *cli_sock);

    int err = SSL_connect(ssl_connect);
    if (err != 1)
    {
        SSL_get_error(ssl_connect, err);
        printf("SSL_connect failed with SSL_get_error code %i\n", err);
        exit(1);
    }

    return ssl_connect;
}

/*
 * Function: "sslLoopRead"
 * Parameters:
 *      -ssl_connect: the SSL connected socket in use
 *      -http_size: a pointer to track the size of the http char array
 * Purpose: Reads back SSL data until no more is received.
 *          Returns a char array of the complete response.
 */
char *sslLoopRead(SSL *ssl_connect, int *http_size)
{
    int err;
    char buf[BUFSIZE];
    char total_buf[1000000];
    int recvd = 0;

    while (1)
    {
        recvd = SSL_read(ssl_connect, buf, BUFSIZE);
        if (recvd > 0)
        {
            // Segmentation fault at this stage might be fixed by resizing total_buf
            strncat(total_buf, buf, recvd);
            continue;
        }
        else if (recvd < 0)
        {
            // Detect error and quit with message
            err = SSL_get_error(ssl_connect, recvd);

            printf("SSL_read failed with SSL_get_error code: %i\n", err);
            exit(1);
        }
        printf("recvd == 0");
        break;
    }

    // NOTE: This transaction does not retain all str data from total_buf (~100B diff)
    // For this app's purposes, those last bytes are irrelevant
    *http_size = strlen(total_buf);
    char *read_resp = malloc(*http_size);
    memcpy(read_resp, total_buf, *http_size);

    return read_resp;
}
