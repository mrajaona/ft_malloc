#include "realloc.h"

void *reallocf(void *ptr, size_t size)
{
    void *nptr;

    nptr = realloc(ptr, size);
    if (nptr == NULL)
        free(nptr);
    return (nptr);
}