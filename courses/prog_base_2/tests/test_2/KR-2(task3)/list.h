#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct list_s * list_t;
int list_size(list_t list);
void *list_change(list_t list, void * data, int pos);
void * list_del(list_t list, int pos);
void list_add(list_t list, void * data, int pos);
list_t list_new();
void * list_get(list_t list, int pos);

#endif // LIST_H_INCLUDED

