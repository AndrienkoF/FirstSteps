#ifndef BLOG_H_INCLUDED
#define BLOG_H_INCLUDED

typedef struct post_s post_t;

post_t * new_post(int length);

void post_delete(post_t * list);
int  post_getLength(post_t * list);
void post_setLength(post_t * list, int newLength);
void post_add(post_t * list,char * userName, char * string, int index, int repost);
void post_remove(post_t * list, int index);
int  post_size(post_t * list);
void post_print(post_t * list);
#endif // BLOG_H_INCLUDED
