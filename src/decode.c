#include "decode.h"
#include "code.h"
#include "work.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int uncompressed(FILE* txt, FILE* lzw)
{
    // массив, куда будут записаны разжатые символы для расшифровки
    int decod[N];
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
    // 3-я лаба конец
    // печать чисел, пригодных к расшифровке
    for (j = 0; j < i; j++) {
        printf("%d\n", decod[j]);
    }
    // вставляем нулевой элемент в будующий словарь
    list_t* head = list_add(0, "", NULL);
    // инициализируем начальный словарь
    head = init_vocabulary(head);

    printf("uncompressed\n");
    return 0;
}
