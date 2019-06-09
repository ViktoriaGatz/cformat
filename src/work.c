#include "work.h"
#include "code.h"
#include "decode.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t* create_list(int key, char* value)
{
    list_t* new = (list_t*)malloc(sizeof(list_t));
    if (new) {
        new->key = key;
        strcpy(new->value, value);
        new->next = NULL;
    }
    return new;
}
/*------------------------------------------------------------------------*/
list_t* list_add(int key, char* value, list_t* head)
{
    list_t* new = create_list(key, value);
    if (new) {
        new->next = head;
        return new;
    }
    return head;
}
/*------------------------------------------------------------------------*/
int lookup(list_t* head, char* s)
{
    list_t* tmp = (list_t*)malloc(sizeof(list_t));
    tmp = head;
    while (tmp != NULL) {
        if (!strcmp(s, tmp->value)) {
            printf("value = %s, key = %d\n", tmp->value, tmp->key);
            return tmp->key;
        }
        tmp = tmp->next;
    }
    return 0;
}
/*------------------------------------------------------------------------*/
list_t* init_vocabulary(list_t* head)
{
    char s[5];
    s[0] = 1;
    s[1] = '\0';
    printf("head %p\n", head);
    for (int i = 1; i < 256; i++) {
        head = list_add(i, s, head);
        if (head) {
            printf("head = %p, head->next = "
                   "%p, head->key = %d, head->value = %s\n",
                   head,
                   head->next,
                   head->key,
                   head->value);
        }
        s[0]++;
    }
    return head;
}
/*------------------------------------------------------------------------*/
void print_vocabulary(list_t* head)
{
    while (head != NULL) {
        printf("key = %d\tvalue = %s\n", head->key, head->value);
        head = head->next;
    }
}
