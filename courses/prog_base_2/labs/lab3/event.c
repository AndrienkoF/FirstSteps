#include "event.h"

void event_subPrint(user_t * user){
	printf("%s:  has been subscribed to Chat!\n\n", user_getName(user));
}
void event_unSubPrint(user_t * user){
	printf("%s:  has been unSubscribed from Chat!\n\n", user_getName(user));
}
void event_newMessagePrint(user_t * user, user_t* author){
	printf("%s:  has been written new message to %s!\n\n", user_getName(author), user_getName(user));
}
