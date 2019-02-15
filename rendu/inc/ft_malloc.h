#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <pthread.h>
# include "ft_malloc_util.h"

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_mem_alloc();

#endif
