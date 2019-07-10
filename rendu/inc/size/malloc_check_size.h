#ifndef MALLOC_CHECK_SIZE_H
# define MALLOC_CHECK_SIZE_H

# include <pthread.h>
# include <stddef.h>

# include <sys/resource.h>
# include <sys/time.h>
# include <limits.h>

# include "global.h"
# include "malloc_good_size.h"

size_t	malloc_check_size(size_t size);

#endif