#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <time.h>

struct string_s{
    char * author;
    char * quote;
    struct tm ourTime;
};

typedef struct string_s string_t;

string_t * string_new();
void string_free(string_t * newString);
void string_fill(string_t * newString, char * author, char * quote, int year, int day, int mon);
char * readTime(string_t * newString);

int initializeWindowsSocketDLL(WSADATA Data);
SOCKET createSocket();
void connecting(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void sendRequest(const char* host_name, SOCKET recvSocket);
void receieve(SOCKET recvSocket, char * buffer);
void receieveSecret(char* buffer, char* host_name, SOCKET recvSocket);
char * readArray(char* buffer);


//void resultPost(SOCKET recvSocket, char* host_name, int maxColIndex);

#endif // CLIENT_H_INCLUDED
