#ifndef REALLOCF_H
# define REALLOCF_H

# include <pthread.h>

# include "global.h"

# include "realloc.h"
# include "free.h"

void	*reallocf_thread(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);

#endif