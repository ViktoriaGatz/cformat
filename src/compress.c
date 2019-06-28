#include "compress.h"
#include "command.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int compress(FILE* lz78, FILE* txt, int N)
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
    // массив со структурами
    phrase_t* phrase = (phrase_t*)malloc(sizeof(phrase_t) * N);
    // массив с фразами
    char array[N][20];
    // массив, где указанно сколько раз употреблялась i-ая фраза
    // int arr[N];
    // нулевой элемент
    scpy(array[0], "");
    phrase[0].n = 0;
    phrase[0].c = 0;

    int tmp = 0;
    char c = 0;
    char* cc = "";
    int done = 0;
    // размер словаря
    while ((c = fgetc(txt)) != EOF) {
        cc = scat_c(cc, c);
        int num = 0;
        for (i = 0; i <= tmp; i++) {
            if (!scmp(cc, array[i])) {
                num = 1;
                break;
            }
        }
        if (num == 0) {
            char word[20];
            scpy(word, cc);
            word[slen(word) - 1] = '\0';
            int number = 0;
            for (i = 0; i <= tmp; i++) {
                if (!scmp(word, array[i])) {
                    number = i;
                }
            }
            tmp++;
            if (tmp > N) {
                printf("dictionary is full\n");
                return 1;
            }
            scpy(array[tmp], cc);
            phrase[tmp].n = number;
            phrase[tmp].c = c;
            cc = "";
        }
    }
    printf("size = %d\n", tmp);

    for (i = 0; i <= (tmp + 1); i++) {
        printf("%d) n = %d\tc = %c\n", i, phrase[i].n, phrase[i].c);
    }
    for (i = 0; i <= (tmp + 1); i++) {
        printf("%d) %s\n", i, array[i]);
    }
    printf("\n");
    write_in_file(lz78, phrase, (tmp + 2));
    printf("compress\n");
    return 0;
}
