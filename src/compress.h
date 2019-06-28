#ifndef COMPRESS
#define COMPRESS
#include <stdio.h>

// структура описывающая фразу (номер фразы и символ, нарушивший соответствие)
typedef struct phrase_s {
    int n;
    char c;
} phrase_t;

int compress(FILE* lz78, FILE* txt, int N);

#endif
