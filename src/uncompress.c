#include "uncompress.h"
#include "command.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
// декодирование
int uncompress(FILE* txt, FILE* lz78, int N)
{
    if (!lz78 || !txt) {
        return 1;
    }
    if (N < 0) {
        return 1;
    }
    int i = 0;
    int size = 0;
    // составление словаря фраз
    phrase_t* phrase = (phrase_t*)malloc(sizeof(phrase_t) * N);
    // декодирование файла
    decode_file(lz78, phrase, &size);
    if (size >= N) {
        printf("Big file, error\n");
        return 1;
    }
    printf("size 3 = %d\n", size);
    for (i = 0; i < size; i++) {
        printf("%d) n = %d\tc = %c\n", i, phrase[i].n, phrase[i].c);
    }
    // массив фраз
    char array[N][20];
    scpy(array[0], "");
    // конкатируем фразы, по принципу, описанному в отчёте
    for (i = 0; i < size; i++) {
        char* ss = (char*)malloc(20);
        ss = scat_c(array[phrase[i].n], phrase[i].c);
        scpy(array[i], ss);
    }
    // запись в итоговый текстовый файл
    for (i = 1; i <= (size + 1); i++) {
        fprintf(txt, "%s", array[i]);
    }
    // добавление пустой строки (если компилятор говорит, что в конце нет пустой
    // строки, то нижестоящую строку следует раскоментарить)
    // fprintf(txt, "\n");
    return 0;
}
