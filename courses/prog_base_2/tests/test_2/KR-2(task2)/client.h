#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <time.h>
#include "socket.h"

struct string_s{
    char author[100];
    char quote[100];
    char time[100];
};

typedef struct string_s string_t;

string_t * string_new();
void string_free(string_t * newString);
void string_fill(string_t * newString, char * author, char * quote, char * time);
char * readTime(string_t * newString);

int initializeWindowsSocketDLL(WSADATA Data);
SOCKET createSocket();
void connecting(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void sendRequest(const char* host_name, SOCKET recvSocket);
void receieve(SOCKET recvSocket, char * buffer);
void receieveSecret(char* buffer, char* host_name, SOCKET recvSocket);
char * readArray(char* buffer);
char* string_authorToJSON(string_t * newString);
void string_fromJSON(string_t* newString, char * string);
void server_info(socket_t* client, const char* worker);

//void resultPost(SOCKET recvSocket, char* host_name, int maxColIndex);

#endif // CLIENT_H_INCLUDED
