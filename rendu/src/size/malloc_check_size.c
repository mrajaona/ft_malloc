#include "malloc_check_size.h"

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
	size_t			max_size;
	struct rlimit	limit;

	if (size == SIZE_MAX)
		return (0);
	size = malloc_good_size_thread(size);
	getrlimit(RLIMIT_AS, &limit);
	max_size = limit.rlim_cur - sizeof(t_elem_info);
	if (max_size < size)
		return (0);
	return (size);
}