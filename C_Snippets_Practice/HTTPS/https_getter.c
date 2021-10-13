/*
    Performs a GET request through HTTPS for any webpage specified in main()
*/

#include "https_setup.h"

/*
 * Function: "getHttpsPage"
 * Parameters:
 *      -url: the base url of the server to connect to
 *      -endpt: the endpoint of the url to connect to
 *      -ctx: the SSL context to build TLS connections from
 * Purpose: Retrieves HTTP data from a given webpage. Returns HTTPS response.
 */
char *getHttpsPage(char *url, char *endpt, SSL_CTX *ctx, int *yt_results_size)
{
    int err;

    SOCKET cli_sock = createSocket(url, "443");
    SSL *ssl_connect = connectTLS(ctx, &cli_sock);

    // Create HTTP GET request
    char request[128];
    sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\n\r\n", endpt, url);

    // Send HTTP request via TLS
    err = SSL_write(ssl_connect, request, sizeof(request));
    if (err == 0)
    {
        printf("Error creating client socket: %d\n", SSL_get_error(ssl_connect, err));
    }

    char *https_resp = sslLoopRead(ssl_connect, yt_results_size);

    // Close/free unused components
    SSL_shutdown(ssl_connect);
    SSL_free(ssl_connect);
    closesocket(cli_sock);

    return https_resp;
}

int main()
{
    startWinSock();

    // *url and *endpt can be changed to GET a different webpage
    char *url = "www.youtube.com";
    char *endpt = "/results?search_query=solar+power";

    SSL_CTX *ctx = createSSL_CTX();
    int yt_results_size = 0;

    char *https_resp = getHttpsPage(url, endpt, ctx, &yt_results_size);

    free(https_resp);

    SSL_CTX_free(ctx);
    WSACleanup();
    return 0;
}
