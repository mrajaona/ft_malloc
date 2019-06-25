#include "malloc.h"

/*
// zone_size % getpagesize == 0
static size_t	calc_zone_size(size_t size)
{
	int	zone_size;

	zone_size = size + sizeof(t_zone_info);
	zone_size = zone_size + (zone_size % getpagesize());
	return (zone_size);
}
*/

void	*malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	(void)size;
	return (ptr);
}