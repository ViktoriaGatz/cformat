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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define RS 30
#define TAB 9
#define LF 10
int* delete_element(int* page, int* size, int c)
{
    int* new = (int*)malloc(sizeof(int) * (*size));
    int j = 0;
    for (int i = 0; i < (*size); i++) {
        if (page[i] == c) {
            i++;
        }
        new[j] = page[i];
        j++;
    }
    page[j] = '\0';
    (*size) = j;
    return new;
}
int* position_tab(int* page, int* size, int c)
{
    page = delete_element(page, size, LF);
    for (int i = 0; i < (*size); i++) {
        printf("%c", page[i]);
        // printf("%d\n", page[i]);
    }
    printf("\n----------------------------\n");
    int delta = 0;
    if (c == 40)
        delta = 1;
    else if (c == 123)
        delta = 2;
    int* result = (int*)malloc(sizeof(int) * 2 * (*size));
    int new_size = (*size);
    int brek_open = 0;
    // int brek_close = 0;
    int j = 0;
    for (int i = 0; i < (*size); i++) {
        if (page[i] == ';') {
            result[j++] = ';';
            result[j++] = LF;
            for (int k = 0; k < brek_open; k++) {
                result[j++] = TAB;
            }
        } else if (page[i] == c) {
            result[j++] = LF;
            for (int k = 0; k < brek_open; k++) {
                result[j++] = TAB;
            }
            brek_open++;
            result[j++] = c;
            result[j++] = LF;
            for (int k = 0; k < brek_open; k++) {
                result[j++] = TAB;
            }
        } else if (page[i] == (c + delta)) {
            brek_open--;
            j--;
            result[j++] = (c + delta);
            result[j++] = LF;
            for (int k = 0; k < brek_open; k++) {
                result[j++] = TAB;
            }
        } else {
            result[j] = page[i];
            j++;
        }
    }
    result[j] = '\0';
    (*size) = j;
    return result;
}
int check_fig(int* page, int size, int c)
{
    int size_page = size;
    int delta = 0;
    if (c == 40)
        delta = 1;
    else if (c == 123)
        delta = 2;
    int i, j;
    for (i = 0; i < size_page; i++) {
        if (page[i] == c) {
            for (j = size_page; j > i; j--) {
                if (page[j] == (c + delta)) {
                    page[i] = 0;
                    page[j] = 0;
                    break;
                }
            }
        }
    }
    int enter = 1;
    j = 1;
    for (i = 0; i < size; i++) {
        if (page[i] == LF) {
            enter++;
            j = 0;
        }
        if (page[i] != 0) {
            fprintf(stderr,
                    "The bracket does not close '%c'. Line %d, symbol %d\n",
                    c,
                    enter,
                    j);
            return 1;
        }
        j++;
    }
    return 0;
}
int slen(int* str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
int sspn(int* page, int c)
{
    if (!page) {
        return -1;
    }
    int j = 0;
    int i = 0;
    while (page[i] != '\0') {
        if (page[i] == c)
            j++;
        i++;
    }
    return j;
}
int sspn_array(int* page, int c, int* check)
{
    if (!page) {
        return -1;
    }
    int j = 0;
    int i = 0;
    while (page[i] != '\0') {
        if (page[i] == c) {
            check[i] = c;
            j++;
        }
        i++;
    }
    return 0;
}
int segmentation(int* page, int* size_page)
{
    int* n = (int*)calloc((*size_page), sizeof(int));
    sspn_array(page, '{', n);
    sspn_array(page, '}', n);
    if (check_fig(n, (*size_page), '{') == -1) {
        return -1;
    }
    free(n);
    int* result;
    result = position_tab(page, size_page, '{');
    minys_enter(result, size_page);
    for (int i = 0; i < (*size_page); i++) {
        printf("%c", result[i]);
    }
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
    int page[n];
    int i = 0;
    while ((page[i] = fgetc(myfile)) != EOF) {
        i++;
    }
    page[i] = '\0';
    int size_page = i;
    /*------------------------------------------------------------------------*/
    if (segmentation(page, &size_page) == -1)
        return -1;

    printf("Done\n");
    return 0;
}
