#ifndef TASK1_H_INCLUDED
#define TASK1_H_INCLUDED

#include "socket.h"
#include "http.h"
#include "student.h"

void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * newStudent);

#endif // TASK1_H_INCLUDED
