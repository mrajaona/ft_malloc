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
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include <sys/time.h>
# include <sys/resource.h>
/*
** int getrlimit(int resource, struct rlimit *rlim);
*/

# include <errno.h>

# include "memory.h"
# include "global.h"
# include "get_type.h"

# include "split.h"

void	*malloc(size_t size);

#endif