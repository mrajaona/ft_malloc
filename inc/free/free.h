#ifndef FREE_H
# define FREE_H

# include <pthread.h>

# include <sys/mman.h>
/*
** int munmap(void *addr, size_t length);
*/

void	free(void *ptr);

#endif