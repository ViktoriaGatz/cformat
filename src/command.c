#include "command.h"
#include "coder.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int write_in_file(FILE* lz78, phrase_t* phrase, int size)
{
    if (!lz78) {
        printf("No file\n");
        return 1;
    }
    printf("size 2 = %d\n", size);
    CodeUnits* code_units = malloc(sizeof(CodeUnits));
    int i = 0;
    for (i = 0; i < size; i++) {
        encode(phrase[i].n, code_units);
        write_code_unit(lz78, code_units);
        fprintf(lz78, "%c", phrase[i].c);
    }
    return 0;
}

int decode_file(FILE* lz78, phrase_t* phrase, int* size)
{
    CodeUnits* code_units = malloc(sizeof(CodeUnits));

    int k;
    uint32_t number;
    code_units->length = 1;
    int i = 0;
    for (k = 1;; k++) {
        ;
        if ((read_next_code_unit(lz78, code_units)) == -1)
            continue;
        number = decode(code_units);
        if (feof(lz78))
            break;

        phrase[i].n = number;
        fread(&phrase[i].c, sizeof(char), 1, lz78);
        i++;
        k++;

        k += code_units->length - 1;
        fseek(lz78, k, SEEK_SET);
    }
    *size = i;
    return 0;
}
