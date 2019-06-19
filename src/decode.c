#include "decode.h"
#include "code.h"
#include "str.h"
#include "work.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* scat(char* s1, char* s2)
{
    // конкатинация первой строки и первого символа второй строки
    if (!s1 || !s2) {
        return NULL;
    }
    int n1 = slen(s1);
    int n2 = slen(s2);
    char* result = (char*)malloc(n1 + n2 + 1);
    int i = 0;
    int j = 0;
    for (i = 0; i < n1; i++) {
        result[i] = s1[i];
    }
    for (j = 0; j < n2; j++) {
        result[j + i] = s2[j];
    }
    result[j + i] = '\0';
    // printf("result (scat) = %s\n", result);
    return result;
}

char* scat_symbol(char* s1, char* s2)
{
    // обычная конкатинация строк
    if (!s1 || !s2) {
        return NULL;
    }
    int n1 = slen(s1);
    char* result = (char*)malloc(n1 + 2);
    int i = 0;
    for (i = 0; i < n1; i++) {
        result[i] = s1[i];
    }
    result[i] = s2[0];
    result[i + 1] = '\0';
    // printf("result (scat) = %s\n", result);
    return result;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    // функция из первой части 3-ей лаболаторной
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

char* lookup_value(list_t* head, int key)
{
    //поиск значения по ключу (возвращает значение в случае успеха, иначе - "0")
    list_t* tmp = (list_t*)malloc(sizeof(list_t));
    tmp = head;
    char* s = (char*)malloc(sizeof(char) * 128);
    while (tmp != NULL) {
        if (key == tmp->key) {
            scpy(s, tmp->value);
            return s;
        }
        tmp = tmp->next;
    }
    return 0;
}

int uncompressed(FILE* txt, FILE* lzw)
{
    // массив, куда будут записаны разжатые символы для расшифровки
    int decod[N] = {0};
    // 3-я лаба начало
    uint8_t* buf = (uint8_t*)malloc(sizeof(uint8_t) * 1500000);
    uint8_t** cur = &buf;
    int i = 0;
    int j = 0;
    int c = 0;
    uint8_t ch = 0;
    while ((c = fread(&ch, sizeof(uint8_t), 1, lzw)) > 0) {
        (*cur)[i] = ch;
        i++;
    }
    cur = &buf;
    while ((decod[j] = decode_varint((const uint8_t**)cur)) > 0) {
        j++;
    }
    int size = j;
    // 3-я лаба конец
    // печать чисел, пригодных к расшифровке
    for (j = 0; j < size; j++) {
        // printf("%d\n", decod[j]);
    }
    // вставляем нулевой элемент в будующий словарь
    list_t* head = list_add(0, "", NULL);
    // инициализируем начальный словарь
    head = init_vocabulary(head);
    // заполняем словарь
    char* value;
    char* tmp1;
    char* tmp2;
    int num = 0;
    int size_vocabulary = 256;

    for (i = 0; i < size; i++) {
        tmp1 = lookup_value(head, decod[num]);
        tmp2 = lookup_value(head, decod[num + 1]);
        if (decod[num + 1] > 255) {
            value = scat_symbol(tmp1, tmp2);
        } else {
            value = scat(tmp1, tmp2);
        }
        head = list_add(size_vocabulary, value, head);
        size_vocabulary++;
        num++;
    }

    free(value);
    free(tmp1);
    free(tmp2);

    // print_vocabulary(head);
    // расшифровываем
    char* tmp;
    char* write_value = "";
    for (i = 0; i < size; i++) {
        tmp = lookup_value(head, decod[i]);
        write_value = scat(write_value, tmp);
        free(tmp);
    }

    if (txt) {
        fwrite(write_value, sizeof(char), slen(write_value), txt);
    }
    printf("uncompressed\n");
    return 0;
}
