#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "../http/http.h"
#include "../socket/socket.h"
#include "../leading/leading.h"

void server_answerRequest(http_request_t request, socket_t* client, leading_t** leadings);

#endif // SERVER_H_INCLUDED
