#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

int initializeWindowsSocketDLL(WSADATA Data);
SOCKET createSocket();
void connecting(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void sendRequest(const char* host_name, SOCKET recvSocket);
void receieve(SOCKET recvSocket, char * buffer);
void receieveSecret(char* buffer, char* host_name, SOCKET recvSocket);

//void resultPost(SOCKET recvSocket, char* host_name, int maxColIndex);

#endif // CLIENT_H_INCLUDED
