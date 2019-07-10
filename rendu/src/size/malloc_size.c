#include "malloc_size.h"

// man 3
size_t	malloc_size_thread(const void *ptr)
{
	t_elem_info	*elem;

	if ((elem = identify(ptr)) != NULL)
		return (elem->size);
	return (0);
}

size_t	malloc_size(const void *ptr)
{
	size_t	ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (0);
	ret = malloc_size_thread(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
