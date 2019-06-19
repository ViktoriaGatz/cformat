#include "work.h"
#include "code.h"
#include "decode.h"
#include "str.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t* create_list(int key, char* value)
{
    //создание листа
    list_t* new = (list_t*)malloc(sizeof(list_t));
    if (new) {
        new->key = key;
        scpy(new->value, value);
        new->next = NULL;
    }
    return new;
}
/*------------------------------------------------------------------------*/
list_t* list_add(int key, char* value, list_t* head)
{
    // добавления листа в список
    list_t* new = create_list(key, value);
    if (new) {
        new->next = head;
        return new;
    }
    return head;
}
/*------------------------------------------------------------------------*/
void list_delete()
{
}
/*------------------------------------------------------------------------*/
int lookup(list_t* head, char* s)
{
    //поиск клоча по значению (возвращает ключ в случае успеха, иначе - "0")
    list_t* tmp = (list_t*)malloc(sizeof(list_t));
    tmp = head;
    while (tmp != NULL) {
        if (!scmp(s, tmp->value)) {
            return tmp->key;
        }
        tmp = tmp->next;
    }
    return 0;
}
/*------------------------------------------------------------------------*/
list_t* init_vocabulary(list_t* head)
{
    // инициализация начального словаря (256 символов расширенной таблицы ASCII)
    char s[5];
    s[0] = 1;
    s[1] = '\0';
    for (int i = 1; i < 256; i++) {
        head = list_add(i, s, head);
        s[0]++;
    }
    return head;
}
/*------------------------------------------------------------------------*/
void print_vocabulary(list_t* head)
{
    // печать словаря
    while (head != NULL) {
        printf("key = %d\tvalue = %s\n", head->key, head->value);
        head = head->next;
    }
}
