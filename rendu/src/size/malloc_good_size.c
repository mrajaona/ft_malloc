#include "malloc_good_size.h"

// man 3
// align 16 bits (2 bytes)
size_t	malloc_good_size_thread(size_t size)
{
	return (size + size % 2);
}

size_t	malloc_good_size(size_t size)
{
	size_t	ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (0);
	ret = malloc_good_size_thread(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
