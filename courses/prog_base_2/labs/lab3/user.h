#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

typedef struct user_s user_t;
typedef struct admin_s admin_t;

typedef void(*cb_subscribe)(user_t * user);
typedef void(*cb_unSubscribe)(user_t * user);
typedef void(*cb_newMessage)(user_t * user, user_t * author);

user_t * user_new(char * name);
void user_delete(user_t * user);

admin_t * user_newAdmin(char * name);
void user_deleteAdmin(admin_t * admin);

void user_setUserEvents(user_t * user, cb_newMessage cb);
void user_setAdminEvents(admin_t * admin, cb_subscribe cb, cb_unSubscribe cb2, cb_newMessage cb3);

char * user_getName(user_t * user);
cb_subscribe admin_getSubCb(admin_t * admin);
cb_unSubscribe admin_getUnSubCb(admin_t * admin);
cb_newMessage user_getNewMessageCb(admin_t * admin, user_t * user);

#endif // USER_H_INCLUDED
