#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "chat.h"
#include "user.h"
#include "event.h"

//unit-test function
static void new_emptyChat_zeroCount(void ** state){
	chat_t * newChat = chat_new();
	assert_int_equal(chat_getQuantityUsers(newChat), 0);
	chat_delete(newChat);
}

static void new_quantityUsers_twoCount(void ** state){
	chat_t * newChat = chat_new();
	user_t * newUser = user_new("Fedya");
	user_t * newUser2 = user_new("Fedya2");
	chat_connectUser(newChat, newUser);
	chat_connectUser(newChat, newUser2);
	assert_int_equal(chat_getQuantityUsers(newChat), 2);
	chat_delete(newChat);
}

static void new_quantityUsers_oneCount(void ** state){
	chat_t * newChat = chat_new();
	user_t * newUser = user_new("Fedya");
	chat_connectUser(newChat, newUser);
	assert_int_equal(chat_getQuantityUsers(newChat), 1);
	chat_delete(newChat);
}

static void new_quantityUsersBeforeUnconnect_zeroCount(void ** state){
	chat_t * newChat = chat_new();
	user_t * newUser = user_new("Fedya");
	chat_connectUser(newChat, newUser);
	chat_unconnectUser(newChat);
	assert_int_equal(chat_getQuantityUsers(newChat), 0);
	chat_delete(newChat);
}

static void new_twoUsersOneUnconnect_oneCount(void ** state){
	chat_t * newChat = chat_new();
	user_t * newUser = user_new("Fedya");
	user_t * newUser2 = user_new("Fedya2");
	chat_connectUser(newChat, newUser);
	chat_connectUser(newChat, newUser2);
	chat_unconnectUser(newChat);
	assert_int_equal(chat_getQuantityUsers(newChat), 1);
	chat_delete(newChat);
}

static void new_connectUser_name(void ** state){
	chat_t * newChat = chat_new();
	user_t * newUser = user_new("Fedya");
	chat_connectUser(newChat, newUser);
	assert_int_equal(strcmp(user_getName(newUser), "Fedya"), 0);
	chat_delete(newChat);
}

static void new_connectUser_nameWrong(void ** state){
	chat_t * newChat = chat_new();
	user_t * newUser = user_new("Fedya");
	chat_connectUser(newChat, newUser);
	assert_int_equal(strcmp(user_getName(newUser), "Nick"), -1);
	chat_delete(newChat);
}

int main(){
	const struct CMUnitTest tests[] = {
	    cmocka_unit_test(new_emptyChat_zeroCount),
	    cmocka_unit_test(new_quantityUsers_twoCount),
		cmocka_unit_test(new_quantityUsers_oneCount),
		cmocka_unit_test(new_quantityUsersBeforeUnconnect_zeroCount),
		cmocka_unit_test(new_twoUsersOneUnconnect_oneCount),
		cmocka_unit_test(new_connectUser_name),
		cmocka_unit_test(new_connectUser_nameWrong),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}


/*
int main(){
	chat_t * newChat = chat_new();
	user_t * newUser1 = user_new("Fedya");
	user_t * newUser2 = user_new("Nick");
	user_t * newUser3 = user_new("Lili");
	user_t * newUser4 = user_new("John");
    admin_t * newAdmin = admin_new("ADMIN Vasya");

	user_setAdminEvents(newAdmin, event_subPrint, event_unSubPrint, event_newMessagePrint);

	user_setUserEvents(newUser1, event_newMessagePrint);
	user_setUserEvents(newUser2, event_newMessagePrint);
    user_setUserEvents(newUser3, event_newMessagePrint);
	user_setUserEvents(newUser4, event_newMessagePrint);

	chat_connectAdmin(newChat, newAdmin);
	chat_connectUser(newChat, newUser1);
	chat_connectUser(newChat, newUser2);
    chat_connectUser(newChat, newUser3);
	chat_connectUser(newChat, newUser4);

	chat_work(newChat);
	chat_delete(newChat);
	return 0;
}*/
