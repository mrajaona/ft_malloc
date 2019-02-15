#include <unistd.h>
#include "ft_malloc.h"

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	free(void *ptr)
{
	if (pthread_mutex_lock(&g_mutex) != 0)
		return ;
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void	*malloc(size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	ret = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	ret = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

void	show_mem_alloc(void *ptr)
{
	if (pthread_mutex_lock(&g_mutex) != 0)
		return ;
	ft_show_mem_alloc(ptr);
	pthread_mutex_unlock(&g_mutex);
}