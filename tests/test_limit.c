#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

int main()
{
	void *ptr;
	size_t size = SIZE_MAX;
	struct rlimit limit;

	getrlimit(RLIMIT_AS, &limit);
	printf("%zu %llu %llu\n", size, limit.rlim_cur, limit.rlim_max);
	ptr = malloc(size);
	printf("%p\n", ptr);
	if (ptr != NULL)
		return (1);
	return (0);
}
