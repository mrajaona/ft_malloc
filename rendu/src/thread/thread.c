#include "ft_malloc.h"

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

// debug
#include "ft_malloc_print.h"
static void	ft_debug(void *addr, size_t size)
{
	char	buf[BUFSIZE];

	ft_clrbuf(buf);
	if (addr)
		ft_put_addr(addr, buf);
	else
		ft_append(buf, "(null)");
	ft_append(buf, " . ");
	ft_put_size(size, buf);
	ft_print_ln(buf, STDOUT);
}

void	free(void *ptr)
{
	if (pthread_mutex_lock(&g_mutex) != 0)
		return ;
	
		write(1, "f ", 2); ft_debug(ptr, 0);
	ft_free(ptr);
		ft_show_mem_alloc();

	pthread_mutex_unlock(&g_mutex);
}

void	*malloc(size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	
		write(1, "m ", 2);
	ret = ft_malloc(size);
		ft_debug(ret, size);
		ft_show_mem_alloc();
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	
		write(1, "r ", 2); ft_debug(ptr, size);
	ret = ft_realloc(ptr, size);
		ft_show_mem_alloc();
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