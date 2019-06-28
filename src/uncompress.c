#include "uncompress.h"
#include "command.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

int uncompress(FILE* txt, FILE* lz78, int N)
{
    if (!lz78 || !txt) {
        printf("kek\n");
        return 1;
    }
    if (N < 0 || N > 2147483647) {
        printf("lol\n");
        return 1;
    }
    int i = 0;
    int size = 0;
    phrase_t* phrase = (phrase_t*)malloc(sizeof(phrase_t) * N);
    decode_file(lz78, phrase, &size);
    if (size >= N) {
        printf("Big file, error\n");
        return 1;
    }
    printf("size 3 = %d\n", size);
    for (i = 0; i < size; i++) {
        printf("%d) n = %d\tc = %c\n", i, phrase[i].n, phrase[i].c);
    }
    char array[N][20];
    scpy(array[0], "");
    for (i = 0; i < size; i++) {
        char* ss = (char*)malloc(20);
        ss = scat_c(array[phrase[i].n], phrase[i].c);
        scpy(array[i], ss);
    }
    for (i = 1; i <= (size + 1); i++) {
        fprintf(txt, "%s", array[i]);
    }
    // fprintf(txt, "\n");
    return 0;
}
