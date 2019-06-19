#ifndef MYSTR_H
#define MYSTR_H
#include <stddef.h>

unsigned int slen(const char* s);
int c_in_str(char c, char* s);
unsigned int sspn(const char* string, const char* reject);
char* stok(char* str, char delim);
int scmp(const char* p1, const char* p2);
char* scpy(char* dst, const char* src);

#endif
