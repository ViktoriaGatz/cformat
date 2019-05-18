/*
Это проект по разработки приложения для автоматического форматирования текста,
написанного на языке С.

Функционал данного проекта:

-> Расстановка табуляции
-> Расстановка переносов строки
-> Разбиение строк, содержащих больше 80 символов
->
->

Немного истории.

Типичный размер страницы — 4096 байт
*/
#include <stdio.h>

int main(int argc, char* argv[])
{
    /*------------------------------------------------------------------------*/
    if (argc != 2) {
        printf("No argument (%s, %d)\n", __FILE__, __LINE__);
        return 1;
    }
    FILE* myfile;
    myfile = fopen(argv[1], "r+t");
    if (!myfile) {
        printf("No file: %s (%s, %d)\n", argv[1], __FILE__, __LINE__);
    }
    /*------------------------------------------------------------------------*/
    return 0;
}
