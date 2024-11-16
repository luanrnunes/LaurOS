#include "string.h"

int strlen(const char* ptr)
{
    int i = 0;

    while(*ptr != 0)
    {
        i++;
        ptr += 1;
    }
    return i;
}

bool isdigit(char c)
{
    return c >= 48 && c <= 57;
}

int asciitonumeric(char c)
{
    return c - 48;
}