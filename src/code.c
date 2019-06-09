#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 65536

typedef struct list_s {
    int key;
    char value[128];
    struct list_s* next;
} list_t;

typedef struct head_s {
    int size;
    list_t* tail;
    list_t* head;
}

list_t*
create_list(int key, char* value)
{
    list_t* new = (list_t*)malloc(sizeof(list_t*));
    if (new) {
        new->key = key;
        strcpy(new->value, value);
        new->next = NULL;
    }
    return new;
}

list_t* list_add(int key, char* value, list_t* head)
{
    list_t* new = create_list(key, value);
    if (new) {
        new->next = head;
        return new;
    }
    return head;
}
list_t* init_vocabulary(list_t* head)
{
    char s[5];
    s[0] = 1;
    s[1] = '\0';
    printf("head %p\n", head);
    for (int i = 1; i < 256; i++) {
        head = list_add(i, s, head);
        if (head) {
        }
        s[0]++;
    }
    return head;
}

void print_vocabulary(list_t* head)
{
    while (head != NULL) {
        printf("key = %d\tvalue = %s\n", head->key, head->value);
        head = head->next;
    }
}

void add_in_head(head_t* head, int key, char* value)
{
    list_t* oldtail = head->tail;
    list_t* new = list_add(key, value, haid->tail);
}

head_t* new_head()
{
    head_t* head = (head_t*)malloc(sizeof(head_t*));
    head->size = 0;
    head->tail = create_list(0, "");
    head->head = NULL;
}

int main()
{
    head_t* head = new_head();
    if (!head) {
        fprintf(stderr, "No head\n");
        return 1;
    }
    add_in_head(head, 0, "");
}
