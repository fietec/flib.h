#define FLIB_IMPLEMENTATION
#include "flib.h"

#define b2s(expr) ((expr)?"true":"false")

int main(int argc, char **argv)
{
    if (argc < 2){
        eprintfn("No input file provided!");
        return 1;
    }
    const char *path = argv[1];
    DIR *dir = opendir(path);
    if (dir == NULL){
        eprintfn("Could not find directory '%s'!", path);
        return 1;
    }
    flib_entry entry;
    while (flib_get_entry(dir, path, &entry)){
        flib_print_entry(entry);
    }
    return 0;
}