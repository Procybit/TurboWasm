// This is an example code

#include <emscripten.h>  // for EMSCRIPTEN_KEEPALIVE
#include "lib/malloc.h"  // for block `malloc` from the extension

extern "C" {  // avoid name mangling
    EMSCRIPTEN_KEEPALIVE  // avoid dead code elimination
    float bar(float a, float b, float c) {
        return (a * b) - c;
    }

    EMSCRIPTEN_KEEPALIVE
    // array argument types MUST correspond to expected array type,
    // otherwise you will never get right values due to wasm memory little-endianess
    void *baz(long long *a, long long *b, size_t length) { 
        long long *c = new long long[length];
        for (size_t i = 0; i < length; i++) {
            c[i] = a[i] * b[i];
        }
        delete[] c;  // only do so if you are sure, better use block `free` from the extension
        return c;
    }
}

