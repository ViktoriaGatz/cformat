#ifndef COMMAND_H
#define COMMAND_H
#include "coder.h"
#include "compress.h"

int write_in_file(FILE* lz78, phrase_t* phrase, int size);
int decode_file(FILE* lz78, phrase_t* phrase, int* size);

#endif
