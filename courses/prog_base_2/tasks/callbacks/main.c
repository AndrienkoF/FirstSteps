#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void (* onClientConnectedCB)(const char *, int);
typedef void (* onClientDisconnected)(const char *, int);

void server (char *mas[], onClientConnectedCB con, onClientDisconnected discon){
    int i;
    char * client[20];
    for (i = 0; i < 10; i++){
        if (mas[i] == '\0'){
            scanf("%s", &client);
            mas[i] = client;
            con(mas[i], i);
        }
        else{
            discon(mas[i], i);
            mas[i] = '\0';
        }
    }
}

void func1(const char * client, int index){
    printf("Connected client >> %s\nHim index: %i\n\n", client, index);
}

void func2(const char * client, int index){
    printf("Disconnected client >> %s\nHim index: %i\n\n", client, index);
}

int main(){
    char * mas[20] = {0};
    mas[1] = "Luck";
    mas[2] = "Lili";
    mas[4] = "Mick";
    mas[7] = "Den";
    onClientConnectedCB con = func1;
    onClientDisconnected discon = func2;
    server(mas, con, discon);
    return 0;
}
