#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chat.h"

struct chat_s{
	user_t * users[MAX_USERS];
	admin_t  * admin;
	int quantityUsers;
};

chat_t * chat_new(){
	chat_t * newChat = malloc(sizeof(struct chat_s));
	newChat->quantityUsers = 0;
	return newChat;
}

void chat_delete(chat_t * self){
	for (int i = 0; i < self->quantityUsers; i++){
		user_delete(self->users[i]);
	}
	free(self);
}

void chat_connectUser(chat_t * chat, user_t * user){
	if (chat->quantityUsers >= MAX_USERS){
		exit(EXIT_SUCCESS);
	}
	chat->users[chat->quantityUsers++] = user;
}

void chat_unconnectUser(chat_t * self){
	if (self->quantityUsers <= 0){
		exit(EXIT_SUCCESS);
	}
	self->users[self->quantityUsers--] = NULL;
}

void chat_connectAdmin(chat_t * chat, admin_t * admin){
	chat->admin = admin;
}

int chat_getQuantityUsers(chat_t * chat){
	return chat->quantityUsers;
}

void chat_work(chat_t * chat){
	for (int i = 0; i < chat->quantityUsers; i++){
		admin_getSubCb(chat->admin)(chat->users[i]);
	}
    while (1){
        int author = rand() % chat->quantityUsers;
        int recipient = rand() % chat->quantityUsers;
        if (recipient != author){
            user_getNewMessageCb(chat->admin, chat->users[recipient])(chat->users[recipient], chat->users[author]);
        }
        Sleep(1000);
	}
}
