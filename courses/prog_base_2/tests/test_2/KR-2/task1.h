#ifndef TASK1_H_INCLUDED
#define TASK1_H_INCLUDED

#include "socket.h"
#include "http.h"

void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * newStudent);
void server_API_info(socket_t * client, http_request_t * req, student_t * newStudent);
void server_invalidResponce(socket_t * client, char * message);

#endif // TASK1_H_INCLUDED
