#ifndef SHOW_ALLOC_MEM_H
# define SHOW_ALLOC_MEM_H

# include <unistd.h>
/*
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include "global.h"

void	show_alloc_mem(void);

#endif