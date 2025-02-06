#ifndef MALLOC_HPP
#define MALLOC_HPP

#include <emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void *_malloc(size_t size) {
        return malloc(size);
    };

    EMSCRIPTEN_KEEPALIVE
    void _free(void *ptr) {
        free(ptr);
    };
}

#endif