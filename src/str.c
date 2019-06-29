#include "str.h"
#include <stdio.h>
#include <stdlib.h>
// конкатинация строк
char* scat(char* s1, char* s2)
{
    if (!s1 || !s2) {
        return NULL;
    }
    int n1 = slen(s1);
    int n2 = slen(s2);
    char* result = (char*)malloc(n1 + n2 + 1);
    int i = 0;
    int j = 0;
    for (i = 0; i < n1; i++) {
        result[i] = s1[i];
    }
    for (j = 0; j < n2; j++) {
        result[j + i] = s2[j];
    }
    result[j + i] = '\0';
    return result;
}
// конкатинация строки и символа
char* scat_c(char* s, char c)
{
    if (!s) {
        char* s = (char*)malloc(2);
        s[0] = c;
        s[1] = '\0';
        return s;
    }
    int n = slen(s);
    char* result = (char*)malloc(n + 2);
    int i = 0;
    for (i = 0; i < n; i++) {
        result[i] = s[i];
    }
    result[i] = c;
    result[i + 1] = '\0';
    return result;
}
/*
char* scat_symbol(char* s1, char* s2)
{
    if (!s1 || !s2) {
        return NULL;
    }
    int n1 = slen(s1);
    char* result = (char*)malloc(n1 + 2);
    int i = 0;
    for (i = 0; i < n1; i++) {
        result[i] = s1[i];
    }
    result[i] = s2[0];
    result[i + 1] = '\0';
    return result;
}
*/
// вычисление длины строки
unsigned int slen(const char* s)
{
    const char* sc = s;
    while (*sc != '\0') {
        ++sc;
    }
    return sc - s;
}
// сравнивание строк
int scmp(const char* p1, const char* p2)
{
    if (!p1 || !p2) {
        return -1;
    }
    const unsigned char* s1 = (const unsigned char*)p1;
    const unsigned char* s2 = (const unsigned char*)p2;
    unsigned char c1, c2;
    do {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    return c1 - c2;
}
// копирование строк
char* scpy(char* dst, const char* src)
{
    if (!src) {
        return NULL;
    }
    if (!dst) {
        dst = (char*)malloc(sizeof(src));
        char* cp = dst;
        while ((*cp++ = *src++))
            ;
        return dst;
    }
    char* cp = dst;
    while ((*cp++ = *src++))
        ;
    return dst;
}
