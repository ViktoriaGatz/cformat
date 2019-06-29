#include "compress.h"
#include "str.h"
#include "uncompress.h"
#include <stdio.h>
#include <stdlib.h>

int compress(FILE* lz78, FILE* txt, int N);
int uncompress(FILE* txt, FILE* lz78, int N);

int main(int argc, char* argv[])
{
    // подсказка, как правильно вводить
    char hint[]
            = "lz78 -c -o file.lz78 file.txt 65536\nlz78 -d -o file1.txt"
              "file.lz78 65536\n";
    if (argc != 6) {
        printf("No argument\n%s", hint);
        return 1;
    }
    FILE* myfile;
    FILE* file;
    int N = 0;
    N = atoi(argv[5]);

    // N - это последнее число, которое записывает пользователь
    // если пользователь вводит отрицательное число, то оно не принимается
    // если число превышающее sizeof(int), то это число оприоре не сможет быть
    // записано в int, оно просто станет отрицательным, поэтому здесь
    // проверка только на то, что число положительное

    // если пользователь введёт слишком маленькое для словаря чило, будет
    // выведена фраза "dictionary is full" ("словарь переполнен")
    // программа не осуществит кодирование
    // удаление фразы сопровождается невозможностью декодирования
    if (N < 0) {
        printf("Big or smal number\n%s", hint);
        return 1;
    }
    if (scmp(argv[2], "-o")) {
        printf("Unknown arg 3\n%s", hint);
        return 1;
    }
    if (!scmp(argv[1], "-c")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        if (compress(myfile, file, N)) {
            // отлавливание ошибок при кодировании
            printf("Error compress\n");
            return 1;
        }
    } else if (!scmp(argv[1], "-d")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        if (uncompress(myfile, file, N)) {
            // отлавливание ошибок при декодировании
            printf("Error uncompress\n");
            return 1;
        }
    } else {
        printf("Unknown arg 2\n");
        return 1;
    }
    fclose(myfile);
    fclose(file);
    return 0;
}
