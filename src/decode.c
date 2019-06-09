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
