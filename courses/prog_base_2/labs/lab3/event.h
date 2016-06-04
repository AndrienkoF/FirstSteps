#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "user.h"

void event_subPrint(user_t * user);
void event_unSubPrint(user_t * user);
void event_newMessagePrint(user_t * user, user_t * author);

#endif // EVENT_H_INCLUDED
