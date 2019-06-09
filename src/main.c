/* clang-format off */
/*
    для размера получаемых кодов является размер словаря во фразах: LZW-коды
    имеют постоянную длину, равную округленному в
    большую сторону двоичному логарифму размера словаря.
    sizeof(vocabulary) = log(2)n * sizeof()
    log(2)512    = 9
    log(2)1024   = 10
    log(2)2048   = 11
    log(2)4096   = 12
    log(2)8192   = 13
    log(2)16384  = 14
    log(2)32768  = 15
  ! log(2)65536  = 16 !
*/
/* clang-format on */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 65536

typedef struct list_s {
    int key;
    char value[128];
    struct list_s* next;
} list_t;

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

list_t* list_add(int key, char* value, list_t* head)
{
    list_t* new = create_list(key, value);
    if (new) {
        new->next = head;
        return new;
    }
    return head;
}

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

void print_vocabulary(list_t* head)
{
    while (head != NULL) {
        printf("key = %d\tvalue = %s\n", head->key, head->value);
        head = head->next;
    }
}

int compress(FILE* lzw, FILE* txt)
{
    char cc;
    char* string = (char*)malloc(sizeof(char) * N);
    int k = 0;
    while ((cc = fgetc(txt)) != EOF) {
        string[k] = cc;
        k++;
    }
    string[k] = '\0';
    printf("string = %s\n", string);

    list_t* head = list_add(0, "", NULL);
    head = init_vocabulary(head);
    printf("\nhead = %p, head->next = %p, head->key = %d\n\n",
           head,
           head->next,
           head->key);
    print_vocabulary(head);
    printf("\nhead = %p, head->next = %p, head->key = %d\n\n",
           head,
           head->next,
           head->key);
    // пополнение словаря
    int result[N];
    int j = 0;
    int key = 256;
    int size = 0;
    int root = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        char* my = (char*)malloc(sizeof(char) * 128);
        memset(my, 0, 128);
        my[j] = string[i];
        printf("// j = %d, i = %d\n", j, i);
        printf("// string %s\n", my);
        while ((root = lookup(head, my))) {
            my[j++] = string[i++];
            printf("j = %d, i = %d\n", j, i);
            printf("string %s\n", my);
        }
        printf("root = %d\n", root);
        head = list_add(key, my, head);
        result[size] = root;
        size++;
        i -= 2;
        j = 0;
        key++;
        free(my);
    }
    printf("size = %d\n", size);

    free(string);
    printf("compress\n");
    return 0;
}

int replenishment()
{
}

int uncompressed(FILE* txt, FILE* lzw)
{
    int decod[N];
    int i = 0;
    char tmp;
    while ((tmp = fgetc(lzw)) != EOF) {
        printf("%c\n", tmp);
        decod[i] = tmp;
        i++;
    }
    printf("i = %d\n", i);

    for (int j = 0; j < i; j++) {
        printf("%d\n", decod[j]);
    }

    list_t* head = list_add(0, "", NULL);
    // head = init_vocabulary(head);
    printf("uncompressed\n");
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 5) {
        printf("No argument\n");
        return 0;
    }
    FILE* myfile;
    FILE* file;
    if (strcmp(argv[2], "-o")) {
        printf("Unknown arg 3\n");
        return 0;
    }
    if (!strcmp(argv[1], "-c")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        compress(myfile, file);
    } else if (!strcmp(argv[1], "-d")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        uncompressed(myfile, file);
    } else {
        printf("Unknown arg 2\n");
        return 0;
    }
    fclose(myfile);
    fclose(file);
    return 0;
}
