#include "calloc.h"

void	*calloc_thread(size_t count, size_t size)
{
	void	*ptr;
	size_t	full_size;

	ptr = malloc_thread(count * size);
	if (ptr)
	{
		full_size = malloc_size_thread(ptr);
		while (full_size)
		{
			full_size--;
			ptr[full_size] = 0;
		}
	}
	return (ptr);
}

void	*calloc(size_t count, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (ptr);
	ret = calloc_thread(count, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}