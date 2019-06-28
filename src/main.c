#include "compress.h"
#include "str.h"
#include "uncompress.h"
#include <stdio.h>
#include <stdlib.h>

int compress(FILE* lz78, FILE* txt, int N);
int uncompress(FILE* txt, FILE* lz78, int N);

int main(int argc, char* argv[])
{
    char hint[]
            = "lz78 -c -o file.lz78 file.txt 65536\nlz78 -d -o file1.txt"
              "file.lz78 65536\n";
    if (argc != 6) {
        printf("No argument\n%s", hint);
        return 1;
    }
    FILE* myfile;
    FILE* file;
    int N = 0;
    N = atoi(argv[5]);
    if (N < 0 || N > 2147483647) {
        printf("Big or smal number\n%s", hint);
        return 1;
    }
    if (scmp(argv[2], "-o")) {
        printf("Unknown arg 3\n%s", hint);
        return 1;
    }
    if (!scmp(argv[1], "-c")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        if (compress(myfile, file, N)) {
            printf("Error compress\n");
            return 1;
        }
    } else if (!scmp(argv[1], "-d")) {
        myfile = fopen(argv[3], "w");
        file = fopen(argv[4], "r");
        if (uncompress(myfile, file, N)) {
            printf("Error uncompress\n");
            return 1;
        }
    } else {
        printf("Unknown arg 2\n");
        return 1;
    }
    fclose(myfile);
    fclose(file);
    return 0;
}
