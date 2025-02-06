#ifndef MALLOC_H
#define MALLOC_H

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void *_malloc(size_t size) {
    return malloc(size);
};

EMSCRIPTEN_KEEPALIVE
void _free(void *ptr) {
    free(ptr);
};


#endif