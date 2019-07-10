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
		return (ptr);
	ret = malloc_good_size_thread(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

// man 3
size_t	malloc_size(const void *ptr)
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
		return (ptr);
	ret = malloc_size_thread(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

#include <sys/resource.h>
#include <sys/time.h>

/*
int main()
{
	void *ptr;
	size_t size = SIZE_MAX;
	struct rlimit limit;

	getrlimit(RLIMIT_AS, &limit);
	printf("%zu %zu %zu\n", size, limit.rlim_cur, limit.rlim_max);
	ptr = malloc(size);
	printf("%p\n", ptr);
	if (ptr != NULL)
		return (1);
	return (0);
}
*/

size_t	malloc_check_size(size_t size)
{
	size_t	max_size;
	struct	rlimit limit;

	size = malloc_good_size(size);
	getrlimit(RLIMIT_AS, &limit);
	max_size = limit.rlim_cur - sizeof(t_elem_info);
	if (max_size < size)
		return (0);
	return (size);
}