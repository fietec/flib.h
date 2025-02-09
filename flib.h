#ifndef _FLIB_H
#define _FLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <sys/stat.h>

#ifndef FLIB_SILENT
    #define flib_error(msg, ...) (fprintf(stderr, "[ERROR] "msg"\n", __VA_ARGS__))
#else
    #define flib_error(msg, ...)
#endif // FLIB_SILENT

#ifndef flib_calloc
#define flib_calloc(c, s) (calloc(c, s))
#endif // flib_calloc

typedef uint64_t fsize_t;

typedef struct{
    char *buffer;
    fsize_t size;
} flib_c;

bool flib_read(const char *path, flib_c *fc);
fsize_t flib_size(const char *path);
bool flib_exists(const char *path);
bool flib_isfile(const char *path);
bool flib_isdir(const char *path);
#endif // _FLIB_H

#ifdef FLIB_IMPLEMENTATION
bool flib_read(const char *path, flib_c *fc)
{
    if (fc == NULL) return false;
    FILE *file = fopen(path, "r");
    if (file == NULL){
        flib_error("Could not open file '%s'!", path);
        return false;
    }
    fsize_t size = flib_size(path);
    char *content = (char*) flib_calloc(size+1, sizeof(char));
    assert(content != NULL && "Out of memory!");
    if (fread(content, sizeof(char), size, file) <= 0){
        flib_error("Could not read file '%s'!", path);
        fclose(file);
        return false;
    }
    fclose(file);
    fc->buffer = content;
    fc->size = size;
    return true;
}

fsize_t flib_size(const char *path)
{
    struct stat attr;
    if (stat(path, &attr) == -1){
        return 0;
    }
    return (fsize_t) attr.st_size;
}

bool flib_exists(const char *path)
{
    struct stat attr;
    return stat(path, &attr) == 0;
}

bool flib_isfile(const char *path)
{
    struct stat attr;
    if (stat(path, &attr) == -1) return false;
    return S_ISREG(attr.st_mode);
}

bool flib_isdir(const char *path)
{
    struct stat attr;
    if (stat(path, &attr) == -1) return false;
    return S_ISDIR(attr.st_mode);
}
#endif // FLIB_IMPLEMENTATION