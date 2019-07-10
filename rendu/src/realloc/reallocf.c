#include "reallocf.h"

void	*reallocf_thread(void *ptr, size_t size)
{
    void *nptr;

    if (!(nptr = realloc_thread(ptr, size)))
        free_thread(ptr);
    return (nptr);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	ret = reallocf_thread(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}