#ifndef DECODE_H
#define DECODE_H
#define N 65536
#include "code.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t decode_varint(const uint8_t** bufp);
int uncompressed(FILE* txt, FILE* lzw);

#endif
