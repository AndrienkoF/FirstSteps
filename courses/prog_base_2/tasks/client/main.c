#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include "client.h"

#pragma comment(lib,"ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480


int main(void) {
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
    receieveSecret(buffer, host_name, recvSocket);
    receieve(recvSocket, buffer);

    // Save matrix in file
    saveMatrixInFile("matrix.txt", buffer);

    // Find max column
    int maxColIndex = indexColumn(buffer);

	printf("\nServer response:\n%s\n", buffer);

    resultPost(recvSocket, host_name, maxColIndex);
    receieve(recvSocket, buffer);

	// Print out receieved socket data
    printf("\n%s\r\n\n", buffer);

    closesocket(recvSocket);
	WSACleanup();

    system("pause");
    return 0;
}
