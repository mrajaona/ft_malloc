#ifndef FREE_H
# define FREE_H

# include <pthread.h>

# include <sys/mman.h>
/*
** int munmap(void *addr, size_t length);
*/

# include "global.h"

void	free(void *ptr);

#endif