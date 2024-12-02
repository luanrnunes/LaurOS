#ifndef STRING_H
#define STRING_H
#include <stdbool.h>

int strlen(const char* ptr);
int strnlen(const char* ptr, int max);
bool isdigit(char c);
int asciitonumeric(char c);

#endif