#ifndef FREE_H
# define FREE_H

# include <pthread.h>

# include <unistd.h>
/*
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include <sys/mman.h>
/*
** int munmap(void *addr, size_t length);
*/

# include "global.h"

# include "identify.h"
# include "merge.h"
# include "get_type.h"

void	free(void *ptr);
void	free_thread(void *ptr);

#endif