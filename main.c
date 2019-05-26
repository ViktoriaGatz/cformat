/*
Этоционал данного проект проект по разработки приложения для автоматического
форматирования текста, написанного на языке С.

Функционал данного проекта:

-> Расстановка табуляции
-> Расстановка переносов строки
-> Разбиение строк, содержащих больше 80 символов
->
->

Немного истории.

Типичный размер страницы — 4096 байт
*/
// Компиляция
// gcc main.c -lMyStr -o main
// ВЫЗОВ:
// ./main log.c
#include <MyStr/MyStr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RS 30 // разделитель записей
#define TAB 9
#define LF 10
void back(char* ss)
{
    char* s = stok(ss, "\n");
    // delete_element()
}
char* tab_back(char* page)
{
    if (!page) {
        return NULL;
    }
    char* ss = strstr(page, "while");
    back(ss);
    while (ss != NULL) {
        ss = strstr(ss, "while");
        back(ss);
    }
}
int delete_element(char* page, char c)
{
    if (!page) {
        exit(1);
    }
    int size = slen(page);
    char* new = (char*)malloc(sizeof(char) * size);
    scpy(new, page);
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (new[i] == c) {
            i++;
        }
        page[j] = new[i];
        j++;
    }
    page[j] = '\0';
    size = j;
    return size;
}
void tab(char* result, int* j, int brek_open)
{
    result[(*j)++] = LF;
    for (int k = 0; k < brek_open; k++) {
        result[(*j)++] = TAB;
    }
}
char* position_tab(char* page, char c)
{
    delete_element(page, LF);
    delete_element(page, TAB);
    int size = slen(page);
    printf("%s\n", page);
    printf("\n----------------------------\n");
    int delta = 0;
    if (c == 40)
        delta = 1;
    else if (c == 123)
        delta = 2;
    char* result = (char*)malloc(sizeof(char) * 2 * size);
    // int new_size = size;
    int brek_open = 0;
    // int brek_close = 0;
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (page[i] == ';') {
            result[j++] = ';';
            tab(result, &j, brek_open);
        } else if (page[i] == c) {
            tab(result, &j, brek_open);
            brek_open++;
            result[j++] = c;
            tab(result, &j, brek_open);
        } else if (page[i] == (c + delta)) {
            brek_open--;
            j--;
            result[j++] = (c + delta);
            tab(result, &j, brek_open);
        } else {
            result[j] = page[i];
            j++;
        }
    }
    result[j] = '\0';
    size = j;
    return result;
}
int check_fig(char* page, int size, char c)
{
    int size_page = size;
    int delta = 0;
    if (c == 40)
        delta = 1;
    else if (c == 123 || c == 91)
        delta = 2;
    int i, j;
    int enter = 1;
    int open = 0;
    int n_symbol = 1;
    for (i = 0; i < size; i++) {
        if (page[i] == LF) {
            enter++;
            n_symbol = 1;
        }
        if (page[i] == c) {
            open++;
        }
        if (page[i] == (c + delta)) {
            open--;
        }
        if (open < 0) {
            fprintf(stderr,
                    "The bracket does not close '%c'. Line %d, symbol %d\n",
                    c,
                    enter,
                    n_symbol);
            return -1;
        }
        j++;
    }
    if (open != 0) {
        fprintf(stderr,
                "The bracket does not close '%c'. Line %d, symbol %d\n",
                c,
                enter,
                n_symbol);
        return -1;
    }
    return 0;
}
int segmentation(char* page, int* size_page)
{
    if (check_fig(page, (*size_page), '{') == -1) {
        return -1;
    }
    if (check_fig(page, (*size_page), '(') == -1) {
        return -1;
    }
    char* result;
    result = position_tab(page, '{');
    // minys_enter(result, size_page);
    /*------------------------------------------------------------------------*/
    printf("%s", result);
    tab_back(result);
    return 0;
}
int main(int argc, char* argv[])
{
    /*------------------------------------------------------------------------*/
    if (argc != 2) {
        fprintf(stderr, "No argument (%s, %d)\n", __FILE__, __LINE__);
        return 1;
    }
    FILE* myfile;
    myfile = fopen(argv[1], "r+t");
    if (!myfile) {
        fprintf(stderr, "No file: %s (%s, %d)\n", argv[1], __FILE__, __LINE__);
    }
    /*------------------------------------------------------------------------*/
    // Only one page
    int n = 4096; // * sizeof(int); // 4096 * sizeof(int) -> 16384
    char page[n];
    int i = 0;
    while ((page[i] = fgetc(myfile)) != EOF) {
        i++;
    }
    page[i - 1] = '\0';
    int size_page = i - 1;
    /*------------------------------------------------------------------------*/
    if (segmentation(page, &size_page) == -1)
        return -1;

    return 0;
}
