#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "cJSON.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

string_t * string_new(){
    string_t * newString = malloc(sizeof(struct string_s));
	strcpy(newString->author, "");
    strcpy(newString->quote, "");
    strcpy(newString->time, "");
	return newString;
}

char* string_getAuthor(string_t* newString){
    return newString->author;
}

char* string_getQuote(string_t* newString){
    return newString->quote;
}

char* string_getDate(string_t* newString){
    return newString->time;
}

void string_free(string_t * newString) {
	free(newString);
}

void string_fill(string_t * newString, char * author, char * quote, char * time) {
	strcpy(newString->author, author);
    strcpy(newString->quote, quote);
    strcpy(newString->time, time);
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

char* string_authorToJSON(string_t * newString){
    char* inJsn = NULL;
    char buffer[300];
    cJSON* stringJsn = cJSON_CreateObject();

    cJSON_AddItemToObject(stringJsn, "author", cJSON_CreateString(newString->author));
    cJSON_AddItemToObject(stringJsn, "quote", cJSON_CreateString(newString->quote));
    cJSON_AddItemToObject(stringJsn, "time", cJSON_CreateString(newString->time));

    inJsn = cJSON_Print(stringJsn);
    cJSON_Delete(stringJsn);
    return inJsn;
}

void string_fromJSON(string_t* newString, char * string){
    cJSON* jList = cJSON_CreateObject();
    jList = cJSON_Parse(string);
    char* author = cJSON_GetObjectItem(jList, "author")->valuestring;
    char* quote = cJSON_GetObjectItem(jList, "quote")->valuestring;

    time_t arrayTime;
    struct tm* ourTime;

    time(&arrayTime);
    ourTime = localtime(&arrayTime);
    string_fill(newString, author, quote, asctime(ourTime));
}

void server_info(socket_t* client, const char* worker){
    char homeBuf[10224];

    sprintf(homeBuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type: application/json\n"
        "Content-Length: %i\r\n\r\n"
        "\n%s", strlen(worker)+1, worker);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

