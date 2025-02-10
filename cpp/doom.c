#include <emscripten.h>
#include "lib/malloc.h"

#include <string.h>
#include <stdint.h>

#include "doom1.wad.h"

#define DOOM_IMPLEMENTATION
#define DOOM_IMPLEMENT_MALLOC
#define DOOM_WIN32
#include "PureDOOM.h"

char** prin_buffer;
int prin_len = 0;

void prin(const char* str) {
    prin_len++;
    prin_buffer = realloc(prin_buffer, prin_len * sizeof(char*));
    prin_buffer[prin_len - 1] = malloc(1024);
    strncpy(prin_buffer[prin_len - 1], str, 1024);
    prin_buffer[prin_len - 1][255] = 0;
}

EMSCRIPTEN_KEEPALIVE
char** retprin() {
    return prin_buffer;
}

EMSCRIPTEN_KEEPALIVE
int lenprin() {
    return prin_len;
}

typedef struct {
    unsigned char* data;
    char* name;
    size_t pos;
    size_t len;
    char eof;
} file_t;

void* opf(const char* name, const char* mode) {
    if (!strcmp(name, "./doom1.wad") && !strcmp(mode, "rb")) {
        file_t* f = malloc(sizeof(file_t));
        f->data = doom1_wad;
        f->name = malloc(strlen(name));
        strcpy(f->name, name);
        f->pos = 0;
        f->len = sizeof(doom1_wad);
        f->eof = 0;
        return f;
    } else {
        return NULL;
    }
}

void clf(void* fv) {
    free(fv);
}

int ref(void* fv, void* buf, int count) {
    file_t* f = (file_t*)fv;
    for (int i = 0; i < count; ++i) {
        if (f->pos <= f->len) {
            memset(buf + i, f->data[f->pos + i], 1);
        } else {
            f->eof = 1;
            return i;
        }
    }
    return count;
}

int wrf(void* fv, const void* buf, int count) {
    return 0;
}

int skf(void* fv, int off, doom_seek_t org) {
    file_t* f = (file_t*)fv;
    switch (org) {
        case DOOM_SEEK_SET:
            f->pos = off;
            break;
        case DOOM_SEEK_CUR:
            f->pos += off;
            break;
        case DOOM_SEEK_END:
            f->len -= off;
            break;
    }
    f->eof = 0;
    return 0;
}

int tlf(void* fv) {
    file_t* f = (file_t*)fv;
    return f->pos;
}

int eof(void* fv) {
    file_t* f = (file_t*)fv;
    return f->eof;
}

int time = 0;

void tm(int* sec, int* usec)
{
    *sec = time / 1000000;
    *usec = time % 1000000;
}

EMSCRIPTEN_KEEPALIVE
void init () {
    char* e[0];

    doom_set_print(&prin);
    doom_set_gettime(&tm);
    doom_set_file_io(&opf, &clf, &ref, &wrf, &skf, &tlf, &eof);

    doom_set_default_int("key_up",          DOOM_KEY_W);
    doom_set_default_int("key_down",        DOOM_KEY_S);
    doom_set_default_int("key_strafeleft",  DOOM_KEY_A);
    doom_set_default_int("key_straferight", DOOM_KEY_D);
    doom_set_default_int("key_use",         DOOM_KEY_E);
    doom_set_default_int("key_fire",        DOOM_KEY_SPACE);

    doom_init(0, e, 0);
}

EMSCRIPTEN_KEEPALIVE
uint8_t* tick(int t) {
    time = t;
    doom_update();
    return doom_get_framebuffer(4);
}

EMSCRIPTEN_KEEPALIVE
void kd(unsigned char code) {
    doom_key_down(code);
}

EMSCRIPTEN_KEEPALIVE
void ku(unsigned char code) {
    doom_key_up(code);
}

EMSCRIPTEN_KEEPALIVE
unsigned long* tick_music() {
    static unsigned long midi_msg[256];
    memset(midi_msg, 0, 256 * (sizeof(unsigned long)));
    for (int i = 0; midi_msg[i] = doom_tick_midi(); ++i);
    return midi_msg;
}