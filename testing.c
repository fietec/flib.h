#define FLIB_IMPLEMENTATION
#include "flib.h"

#define b2s(expr) ((expr)?"true":"false")

int main(int argc, char **argv)
{
    if (argc < 2){
        fprintf(stderr, "[ERROR] No input file provided!\n");
        return 1;
    }
    const char *path = argv[1];
    flib_c content;
    if (!flib_read(path, &content)) return 1;
    printf("%s: '%s' (%llu bytes)\n", path, content.buffer, content.size);
    return 0;
}