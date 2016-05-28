#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "client.h"
#include "socket.h"

#pragma comment(lib,"ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480


int main(void) {
    string_t* newString = string_new();
    socket_t* server = socket_new();

    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);

    // Initialize Windows Socket DLL
    status = initializeWindowsSocketDLL(Data);

	// Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT);              // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET;                // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip);    // specify ip address

	// Create socket
	recvSocket = createSocket();

    // Connect
    connecting(recvSocket, recvSockAddr);

    // Send request
    sendRequest(host_name, recvSocket);

	// Receieve
	receieve(recvSocket, buffer);


	printf("\nServer response:\n%s\n", buffer);

    //receieve(recvSocket, buffer);

	// Print out receieved socket data
    //printf("\n%s\n\n", readArray(buffer));

    while(true){
        puts("Waiting...");
        socket_t* client = socket_accept(server);

        if(socket_read(client, buffer, sizeof(buffer)) <=0){
            socket_close(client);
            socket_free(client);
            continue;
        }

        printf("Request:\n%s\n", buffer);

        char str[200];
        strcpy(str, readArray(buffer));

        string_fromJSON(newString, str);
        char * send = string_authorToJSON(newString);
        server_info(client, send);

        socket_free(client);
    }


    socket_free(server);

    string_free(newString);

    closesocket(recvSocket);
	WSACleanup();


    return 0;
}
