#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#include "http/http.h"
#include "leading/leading.h"
#include "socket/socket.h"
#include "read.h"

#define PORT 5000


int main(){
    lib_init();
    leading_t* leadings[MAX_LEADINGS];
    for(int i = 0; i < MAX_LEADINGS; i++){
        leadings[i] = leading_new();
    }

    read_parseLeadings(leadings);

    socket_t* server = socket_new();
    socket_bind(server, PORT);
    socket_listen(server);

    char buffer[10000];
    while(true){
        puts("Waiting for client...!");
        socket_t * client = socket_accept(server);

        if(kbhit()){
            char e = getch();
            if(e == 'm'){
                socket_free(client);
                break;
            }
        }

        if(socket_read(client, buffer, sizeof(buffer)) <= 0){
            socket_close(client);
            socket_free(client);
            continue;
        }

        printf("Request:\n%s\n", buffer);

        http_request_t request = http_request_parse(buffer);

        server_answerRequest(request, client, leadings);

        socket_free(client);
    }

    for(int i = 0; i<MAX_LEADINGS; i++)
        leading_free(leadings[i]);

    socket_free(server);
    lib_free();
    return 0;
}
