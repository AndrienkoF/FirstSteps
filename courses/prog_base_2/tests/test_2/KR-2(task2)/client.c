#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

string_t * string_new(){
    string_t * newString = malloc(sizeof(struct string_s));
	return newString;
}

void string_free(string_t * newString) {
	free(newString);
}

void string_fill(string_t * newString, char * author, char * quote, int year, int day, int mon) {
	newString->author = author;
	newString->quote = quote;
	newString->ourTime.tm_year = year;
	newString->ourTime.tm_mday = day;
	newString->ourTime.tm_mon = mon;
}

char * readTime(string_t * newString){
    char str[100];
    sprintf("%i-%i-%i", newString->ourTime.tm_year, newString->ourTime.tm_mday, newString->ourTime.tm_mon );
    return str;
}

int initializeWindowsSocketDLL(WSADATA Data){
    int status;
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0){
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
    return status;
}

SOCKET createSocket(){
    SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(recvSocket == INVALID_SOCKET){
		printf("ERROR: socket unsuccessful\r\n");
		system("pause");
		return 0;
	}
	return recvSocket;
}

void connecting(SOCKET recvSocket, SOCKADDR_IN recvSockAddr){
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }

}

void sendRequest (const char* host_name, SOCKET recvSocket){
    char request[200];
    sprintf(request, "GET /test/var/4?format=json HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);
    send(recvSocket, request, strlen(request), 0);
}

void receieve(SOCKET recvSocket, char * buffer){
    int status;
    int numrcv;
    numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
}

char * readArray(char* buffer){
    char arrayJSON[400];
    char * firstPoint;
    char* str;
    firstPoint = strstr(buffer, "Content-Length:");
    str = strtok(firstPoint, "\n");
    str = strtok(NULL, "\n");
    str = strtok(NULL, "\n");
    strcpy(arrayJSON, str);
    arrayJSON[strlen(arrayJSON)] = '\0';
    return arrayJSON;
}

/*
static cJSON * string_serializeJSON(const string_t * newString) {
	cJSON * studSmpJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(studSmpJSON, "author", cJSON_CreateString(newStudent->author));
	cJSON_AddItemToObject(studSmpJSON, "quote", cJSON_CreateString(newStudent->quote));
    sprintf("%i-%i-%i", newString->ourTime.tm_year, newString->ourTime.tm_mday, newString->ourTime.tm_mon );

	return studSmpJSON;
}*/
