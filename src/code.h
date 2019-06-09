#ifndef CODE_H
#define CODE_H
#define N 65536
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list_s {
    int key;
    char value[128];
    struct list_s* next;
} list_t;

int compress(FILE* lzw, FILE* txt);
list_t* lzw_code(char* string, int* result, list_t* head, int* k);
int code(FILE* lzw, int* result, int k);
size_t encode_varint(uint32_t value, uint8_t* buf);

#endif
