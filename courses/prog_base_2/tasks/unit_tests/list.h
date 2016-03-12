#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct post_s post_t;

post_t * new_post(int length);

void memory_delete(post_t * list);
int  post_getLength(post_t * list);
void post_setLength(post_t * list, int newLength);
int  post_add(post_t * list,char * userName, char * string, int index, int repost);
int  post_remove(post_t * list, int index);
int  post_size(post_t * list);
void post_print(post_t * list);
int  largestNumRepost(post_t * list);
int  reposMoreThanGivenNum(post_t * list, int giveNum);

#endif // LIST_H_INCLUDED
