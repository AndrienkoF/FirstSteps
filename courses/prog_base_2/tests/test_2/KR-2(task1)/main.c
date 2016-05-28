#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "task1.h"

static socket_t * winSock;

int main(){
	student_t * newStudent = student_new();
	student_fill(newStudent, "Fedya Anrienko", "KP-51", 4);

	int PORT = 5000;
	lib_init();
	winSock = socket_new();

	if (socket_bind(winSock, PORT) == SOCKET_ERR) {
		printf("Cannot bind %i port\n", PORT);
		socket_close(winSock);
		socket_free(winSock);
		return 0;
	}

	socket_listen(winSock);
	char buf[10000];
	socket_t * client = NULL;

	while (1) {
		printf("Awaiting for connections...\n");
		client = socket_accept(winSock);

		if (client == NULL) {
			printf("NULL client, closing app...\n");
			break;
		}

		int readStatus = socket_read(client, buf, sizeof(buf));

		if (readStatus <= 0) {
			printf("Empty request, skipping...\n");
			socket_close(client);
			socket_free(client);
			continue;
		}

		printf(">> Got request (readStatus: %i):\n'%s'\n", readStatus, buf);
		http_request_t request = http_request_parse(buf);

		server_analyzeRequest(&request, client, newStudent);

		socket_free(client);
	}

	socket_close(winSock);
	socket_free(winSock);

    student_free(newStudent);

	lib_free();

    return 0;
}
