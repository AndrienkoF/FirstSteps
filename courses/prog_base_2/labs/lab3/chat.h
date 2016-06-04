#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

#include "user.h"

#define MAX_USERS 5

typedef struct chat_s chat_t;

chat_t * chat_new();
void chat_delete(chat_t * chat);
int chat_getQuantityUsers(chat_t * chat);
void chat_connectUser(chat_t * chat, user_t * user);
void chat_connectAdmin(chat_t * chat, admin_t * admin);
void chat_unconnectUser(chat_t * chat);

void chat_work(chat_t * chat);

#endif // CHAT_H_INCLUDED
