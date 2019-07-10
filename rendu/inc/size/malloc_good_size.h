#ifndef MALLOC_GOOD_SIZE_H
# define MALLOC_GOOD_SIZE_H

# include <pthread.h>
# include <stddef.h>

# include "global.h"

size_t	malloc_good_size_thread(size_t size);
size_t	malloc_good_size(size_t size);

#endif