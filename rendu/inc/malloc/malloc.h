#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>

# include <sys/mman.h>
/*
** void *mmap(void *addr, size_t length, int prot, int flags, int fd,
** off_t offset);
*/

# include <unistd.h>
/*
** int getpagesize(void);
*/

# include <sys/time.h>
# include <sys/resource.h>
/*
** int getrlimit(int resource, struct rlimit *rlim);
*/

# include "memory.h"

void	*malloc(size_t size);

#endif