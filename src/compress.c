#include "compress.h"
#include "command.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// кодирование
int compress(FILE* lz78, FILE* txt, int N)
{
    if (!lz78 || !txt) {
        printf("kek\n");
        return 1;
    }
    if (N < 0) {
        printf("lol\n");
        return 1;
    }
    int i = 0;
    // массив со структурами
    phrase_t* phrase = (phrase_t*)malloc(sizeof(phrase_t) * N);
    // массив с фразами
    char array[N][20];
    // нулевой элемент
    scpy(array[0], "");
    phrase[0].n = 0;
    phrase[0].c = 0;

    int tmp = 0;
    char c = 0;
    char* cc = "";
    int done = 0;
    // чтение из файла
    while ((c = fgetc(txt)) != EOF) {
        cc = scat_c(cc, c);
        int num = 0;
        // tmp - размер словаря
        for (i = 0; i <= tmp; i++) {
            if (!scmp(cc, array[i])) {
                // если фраза уже была, то делаем метку и выходим из цикла
                num = 1;
                break;
            }
        }
        // если фраза уже была (num = 1), то конкатируем ещй один символ
        // и обнуляем метку (34-35)
        // если такой строки ещй не было (num = 0), то добавляем эту фразу в
        // словарь, а в структуру добавляем число - номер строки (этой же строки
        // только без последнего символа (67 строка))
        // и этот последний символ (68 строка)
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
            // если этой фразы ещё не было, то добавляем её в словарь
            scpy(array[tmp], cc);
            phrase[tmp].n = number;
            phrase[tmp].c = c;
            cc = "";
        }
    }
    printf("size = %d\n", tmp);
    // вывод кодов из словаря
    for (i = 0; i <= (tmp + 1); i++) {
        printf("%d) n = %d\tc = %c\n", i, phrase[i].n, phrase[i].c);
    }
    printf("\n");
    // запись в файл
    write_in_file(lz78, phrase, (tmp + 2));
    printf("compress\n");
    return 0;
}
