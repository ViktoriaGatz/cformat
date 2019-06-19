#include "code.h"
#include "decode.h"
#include "str.h"
#include "work.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int compress(FILE* lzw, FILE* txt)
{
    // читаем из текстового файла
    char cc;
    char* string = (char*)malloc(sizeof(char) * N);
    int k = 0;
    while ((cc = fgetc(txt)) != EOF) {
        string[k] = cc;
        k++;
    }
    string[k] = '\0';
    // добавляем нулевой элемент в будующий словарь
    list_t* head = list_add(0, "", NULL);
    // инициализируем словарь
    head = init_vocabulary(head);
    // пополнение словаря
    int* result = (int*)malloc(sizeof(int) * N);
    head = lzw_code(string, result, head, &k);
    for (int l = 0; l < k; l++) {
        // printf("result[%d] =  %d\n", l, result[l]);
    }
    // print_vocabulary(head);
    free(string);
    // дополнительно сжимаем (3-я лаба)
    if (!code(lzw, result, k))
        printf("compress\n");
    return 0;
}
/*------------------------------------------------------------------------*/
list_t* lzw_code(char* string, int* result, list_t* head, int* k)
{
    // процесс кодирования
    int j = 0;
    int key = 256;
    int size = 0;
    int root = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        char* my = (char*)malloc(sizeof(char) * 128);
        if (i >= *k) {
            result[size] = 10;
            *k = size + 1;
            return head;
        }
        my[j] = string[i];
        while (lookup(head, my)) {
            root = lookup(head, my);
            if (i >= *k) {
                result[size] = 10;
                *k = size + 1;
                return head;
            }
            my[j++] = string[i++];
        }
        head = list_add(key, my, head);
        result[size] = root;
        size++;
        i -= 2;
        j = 0;
        key++;
        free(my);
    }
    return head;
}
/*------------------------------------------------------------------------*/
int code(FILE* lzw, int* result, int k)
{
    // 3-я лаба
    uint8_t tmp;
    uint8_t* buf = (uint8_t*)malloc(sizeof(uint8_t) * 1500000);

    uint32_t z;
    for (int i = 0; i < k; i++) {
        z = result[i];
        tmp = encode_varint(z, buf);
        fwrite(buf, sizeof(uint8_t), tmp, lzw);
    }
    return 0;
}
/*------------------------------------------------------------------------*/
size_t encode_varint(uint32_t value, uint8_t* buf)
{
    // 3-я лаба, первая часть
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}
