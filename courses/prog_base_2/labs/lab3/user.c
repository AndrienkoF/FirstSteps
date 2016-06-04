#include "user.h"

struct user_s{
	char name[50];
	cb_newMessage messageCb;
};

struct admin_s{
	char name[50];
	cb_subscribe subscribeCb ;
	cb_unSubscribe unSubscribeCb ;
	cb_newMessage messageCb;
};

user_t * user_new(char * name){
	user_t * newUser = malloc(sizeof(struct user_s));
	strcpy(newUser->name, name);
	return newUser;
}

void user_delete(user_t * user){
	free(user);
}

admin_t * admin_new(char * name){
	admin_t * newAdmin = malloc(sizeof(struct admin_s));
	strcpy(newAdmin->name, name);
	return newAdmin;
}

void admin_delete(admin_t * admin){
	free(admin);
}

void user_setUserEvents(user_t * user, cb_newMessage messageCb){
	user->messageCb = messageCb;
}

void user_setAdminEvents(admin_t * admin, cb_subscribe subscribeCb, cb_unSubscribe unSubscribeCb, cb_newMessage messageCb){
	admin->subscribeCb = subscribeCb;
	admin->unSubscribeCb = unSubscribeCb;
	admin->messageCb;
}

char * user_getName(user_t * user){
	return user->name;
}

cb_subscribe admin_getSubCb(admin_t * admin){
	return admin->subscribeCb;
}

cb_unSubscribe admin_getUnSubCb(admin_t * admin){
	return admin->unSubscribeCb;
}

cb_newMessage user_getNewMessageCb(admin_t * admin, user_t * user){
	return user->messageCb;
}
