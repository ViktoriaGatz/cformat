#ifndef WORK_H
#define WORK_H
#include "code.h"

list_t* create_list(int key, char* value);
list_t* list_add(int key, char* value, list_t* head);
int lookup(list_t* head, char* s);
list_t* init_vocabulary(list_t* head);
void print_vocabulary(list_t* head);

#endif
