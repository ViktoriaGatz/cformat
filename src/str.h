#ifndef STR_H
#define STR_H

char* scat(char* s1, char* s2);
char* scat_c(char* s, char c);
char* scat_symbol(char* s1, char* s2);
unsigned int slen(const char* s);
int scmp(const char* p1, const char* p2);
char* scpy(char* dst, const char* src);

#endif
