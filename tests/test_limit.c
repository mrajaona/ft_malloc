#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
	void *ptr;
	struct rlimit limit;

	getrlimit(RLIMIT_AS, &limit);
	printf("%llu\n%ld\n%llu\n%llu\n",
		SIZE_MAX, SSIZE_MAX, 
		limit.rlim_cur, limit.rlim_max);
	ptr = malloc(SIZE_MAX);
	printf("address >> %p\n", ptr);
	if (ptr != NULL)
		return (1);
	return (0);
}
