#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON.h"
#include "task1.h"

static cJSON * investor_serializeJSON(const student_t * newStudent) {
	cJSON * studSmpJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(studSmpJSON, "name", cJSON_CreateString(newStudent->name));
	cJSON_AddItemToObject(studSmpJSON, "group", cJSON_CreateString(newStudent->group));
	cJSON_AddItemToObject(studSmpJSON, "variant", cJSON_CreateNumber(newStudent->variant));

	return studSmpJSON;
}

char * student_parseToJSON(const student_t * newStudent) {
	cJSON * studentJSON = investor_serializeJSON(newStudent);
	char * buffJSON = cJSON_Print(studentJSON);
	cJSON_Delete(studentJSON);
	return buffJSON;
}

void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * newStudent) {
    if (strcmp(request->uri, "/info") == 0 || strcmp(request->uri, "/info/") == 0) {
        server_API_info(client, request, newStudent);
    }else {
        server_invalidResponce(client, "Invalid path.");
    }
}

void server_API_info(socket_t * client, http_request_t * req, student_t * newStudent) {
    char strBuf[10240];
    if (strcmp(req->method, "GET") == 0) {
        char * studentJSON = student_parseToJSON(newStudent);
        sprintf(strBuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type: application/json\n"
        "Content-Length: %zu\n"
        "Connection: keep-alive\n"
        "\n%s", strlen(studentJSON), studentJSON);
        free(studentJSON);
    }else{
        server_invalidResponce(client, "Invalid command.");
        return;
    }
    socket_write_string(client, strBuf);
    socket_close(client);
}

void server_invalidResponce(socket_t * client, char * message) {
    char strBuf[1024];
    char * errText = message;
    sprintf(strBuf,
    "HTTP/1.1 404 \n"
    "Content-Type: application/json\n"
    "Content-Length: %zu\n"
    "\n%s", strlen(errText), errText);
    socket_write_string(client, strBuf);
    socket_close(client);
}





