#include "MyStr.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int slen(const char* s)
{
    const char* sc = s;
    while (*sc != '\0') {
        ++sc;
    }
    return sc - s;
}
int scmp(const char* p1, const char* p2)
{
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
char* scpy(char* dst, const char* src)
{
    char* cp = dst;
    while ((*cp++ = *src++))
        ;
    return dst;
}
