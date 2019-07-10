#include "realloc.h"

void *reallocf(void *ptr, size_t size)
{
    void *nptr;

    if (!(nptr = realloc(ptr, size)))
        free(ptr);
    return (nptr);
}