#ifndef CALLOC_H
# define CALLOC_H

# include <pthread.h>

# include "malloc_size.h"

void *calloc_thread(size_t count, size_t size);
void *calloc(size_t count, size_t size);

#endif