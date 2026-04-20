#include <cstdio>
#include "assert.hpp"


static size_t failedCount = 0;
static size_t trueCount = 0;


int assertFail(const char* expr, const char* file, size_t line){
    fprintf(stderr, "\033[31;1m%s:%zu: %s FAILED\033[0m\n", file, line, expr);
    failedCount++;
    return 0;
}

int assertTrue(const char* expr, const char* file, size_t line){
    fprintf(stderr, "\033[32;1m%s:%zu: %s SUCCESS\033[0m\n", file, line, expr);
    trueCount++;
    return 0;
}

int assertFunction(int function, const char* expr, const char* file, size_t line) {
    if(function) {
        return assertTrue(expr, file, line);
    }
    else {
        return assertFail(expr, file, line);
    }
}

size_t getTrueTests() {
    return trueCount;
}

size_t getFailedTests() {
    return failedCount;
}
