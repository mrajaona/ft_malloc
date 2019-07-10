#ifndef MALLOC_SIZE_H
# define MALLOC_SIZE_H

# include <pthread.h>
# include <stddef.h>

# include "global.h"
# include "memory.h"
# include "identify.h"

size_t	malloc_size_thread(const void *ptr);
size_t	malloc_size(const void *ptr);

#endif