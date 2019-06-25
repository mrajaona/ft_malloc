#ifndef REALLOC_H
# define REALLOC_H

// # include <pthread.h>

# include <unistd.h>
/*
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include "malloc.h"
# include "free.h"
# include "ft_memcpy.h"

# include "memory.h"
# include "global.h"

void	*realloc(void *ptr, size_t size);

#endif