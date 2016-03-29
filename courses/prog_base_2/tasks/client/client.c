#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

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
    sprintf(request, "GET /var/6 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
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

void receieveSecret(char* buffer, char* host_name, SOCKET recvSocket){
    char secret[50];
	char request[200];
	strcpy(secret, strstr(buffer, "secret"));
	sprintf(request, "GET /var/6?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
	send(recvSocket, request, strlen(request), 0);
}

void saveMatrixInFile(const char * pwrite, char* buffer){
    int i,j;
    char * token;
    char * firstPoint;
    char ** matrix;
	FILE * fw = fopen(pwrite, "w");
	if ((fw = fopen(pwrite, "w")) == NULL ) {
		printf("Cannot open file.\n");
		return;
	}

    firstPoint = strstr(buffer,"Content-Length: 43");

    token = strtok(firstPoint, "\n");
    token = strtok(NULL, "\n");

    while(token != NULL){
        matrix = token;
        fprintf(fw, "%s ", matrix);
        token = strtok(NULL, " ");
    }

    fclose(fw);
}

int fileLength(const char * pread){
	int c;
	int lines = 0;
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	do {
		c = fgetc(fr);
		if (c == '\n') {
			lines++;
		}
	} while (c != EOF);
	fclose(fr);
	return lines;
}

void downloadMatrix(const char * pread, int massiv[20][20]){
	int i, j;
	char clip[100];
	int lines;
	FILE * fr = fopen(pread, "r");
	if ((fr = fopen(pread, "r")) == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	lines = fileLength("matrix.txt");
	for (i = 0; i <= lines; i++) {
		fgets(clip, 100, fr);
		sscanf(clip, "%i %i %i %i", &massiv[i][0], &massiv[i][1], &massiv[i][2], &massiv[i][3]);
	}
	fclose(fr);
}

int indexColumn(char* buffer){
    int i, j, sumCol, temp = 0;
    int length = fileLength("matrix.txt");
    int massiv[20][20];
    downloadMatrix("matrix.txt", massiv);

    for (i = 0; i <= length; i++){
        sumCol = 0;
        for (j = 0; j <= length; j++){
            sumCol = sumCol + massiv[j][i];
        }
        if(sumCol > temp){
            temp = i;
        }
    }
	return temp;
}

void resultPost(SOCKET recvSocket, char* host_name, int maxColIndex){
	char result[30];
	char request[200];
	sprintf(result, "result=%d", maxColIndex);
	printf("Max column index: %d\n", maxColIndex);
	sprintf(request, "POST /var/6 HTTP/1.0\r\n"
		"Host: %s\r\n"
		"Content-length: %d\r\n\r\n"
		"%s\r\n", host_name, strlen(result), result);
	send(recvSocket, request, strlen(request) + 1, 0);
}



