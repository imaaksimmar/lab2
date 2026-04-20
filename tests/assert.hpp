#pragma once
#include <cstddef>

int assertFail(const char* expr, const char* file, size_t line);
int assertTrue(const char* expr, const char* file, size_t line);
int assertFunction(int function, const char* expr, const char* file, size_t line);

size_t getTrueTests();
size_t getFailedTests();

#define assert(func) assertFunction((func), #func, __FILE__, __LINE__);
