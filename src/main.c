/* clang-format off */
/*
    АЛГОРИТМ LZW;
    для размера получаемых кодов является размер словаря во фразах: LZW-коды
    имеют постоянную длину, равную округленному в
    большую сторону двоичному логарифму размера словаря.
    sizeof(vocabulary) = log(2)n * sizeof()
    log(2)512    = 9
    log(2)1024   = 10
    log(2)2048   = 11
    log(2)4096   = 12
    log(2)8192   = 13
    log(2)16384  = 14
    log(2)32768  = 15
  ! log(2)65536  = 16 !
  РЕАЛИЗАЦИЯ НА ОСНОВЕ СПИСКА
  Тем самым, мы можем добавлять элементы в словарь пока не кончится память
  на устройстве.

  ПРОЦЕСС КОДИРОВАНИЯ
  ./main -c -o my.lzw my.txt

  ПРОЦЕСС ДЕКОДИРОВАНИЯ
  ./main -d -o result.txt my.lzw

  СРАВНЕНИЕ ФАЙЛОВ
  diff my.txt result.txt
  */
/* clang-format on */
#include "code.h"
#include "decode.h"
#include "str.h"
#include "work.h"
#include <stdio.h>
#define N 65536

int main(int argc, char* argv[])
{
    if (argc != 5) {
        printf("No argument\n");
        return 0;
    }
    FILE* myfile;
    FILE* file;
    if (scmp(argv[2], "-o")) {
        printf("Unknown arg 3\n");
        return 0;
    }
    if (!scmp(argv[1], "-c")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        compress(myfile, file);
    } else if (!scmp(argv[1], "-d")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        uncompressed(myfile, file);
    } else {
        printf("Unknown arg 2\n");
        return 0;
    }
    fclose(myfile);
    fclose(file);
    return 0;
}
