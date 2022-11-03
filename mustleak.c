#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MUSTLEAK_DEBUG "MUSTLEAK_DEBUG"
#define MUSTLEAK_MB_PER_SEC "MUSTLEAK_MB_PER_SEC"
#define MUSTLEAK_STOP_COUNT "MUSTLEAK_STOP_COUNT"

#define DEBUG(...) {\
    if (debug) {\
        fprintf(stdout, __VA_ARGS__);\
    }\
}
#define ERROR(...) {\
    fprintf(stderr, __VA_ARGS__);\
}

static pthread_t leaking_thread;
static int debug = 0;

// by default, leak 1MB per second.
static int MB_per_sec = 1;

// by default, stop leaking after 100 times.
static int stop_count = 100;

static void* leaking(void *args) {
    int leaking_rate = MB_per_sec * 1024 * 1024;
    int remain = stop_count;
    while (remain-- > 0) {
        void* p = malloc(leaking_rate);
        memset(p, 1, leaking_rate);

        DEBUG("Pid %d leaks %dMB memory located at %p\n", getpid(), MB_per_sec, p);
        sleep(1);;
    }
    DEBUG("Leaking stopped after %d times\n", stop_count);
    return NULL;
}

static void create_thread() {
    int err;
    err = pthread_create(&leaking_thread, NULL, leaking, NULL);
    if (err != 0) {
        ERROR("Can't create leaking thread:%s\n", strerror(err));
    }
    DEBUG("Create leaking thread successfully\n")
}

static void parse_env() {
    char* debug_str = getenv(MUSTLEAK_DEBUG);
    if (debug_str != NULL) {
        debug = atoi(debug_str) > 0 ? 1 : 0;
    }
    char* MB_per_sec_str = getenv(MUSTLEAK_MB_PER_SEC);
    if (MB_per_sec_str) {
        int v = atoi(MB_per_sec_str);
        MB_per_sec = v > 0 ? v : MB_per_sec;
    }
    char* stop_count_str = getenv(MUSTLEAK_STOP_COUNT);
    if (stop_count_str) {
        int v = atoi(stop_count_str);
        stop_count = v > 0 ? v : stop_count;
    }
}

static void __attribute__((constructor)) init() {
    parse_env();
    create_thread();
}