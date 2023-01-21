#include <stdlib.h>

char *str[1000000000];
int i  = -1;
void *maloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    str[++i] = ptr;
    return ptr;
}