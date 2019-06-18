#ifndef REALLOC_H
# define REALLOC_H

# include <pthread.h>

# include "malloc.h"
# include "free.h"
# include "ft_memcpy.h"

# include "size.h"

void	*realloc(void *ptr, size_t size);

#endif