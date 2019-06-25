#include "malloc.h"
/*
// zone_size % getpagesize == 0
static size_t	calc_zone_size(size_t size)
{
	int	zone_size;

	zone_size = size + sizeof(t_zone_info);
	zone_size = zone_size + (getpagesize() - (zone_size % getpagesize()));
	return (zone_size);
}
*/

// add to start of list
static void	*large(size_t size)
{
	t_elem_info	*new;
	
	size = size + sizeof(t_elem_info);
	size = size + (getpagesize() - (size % getpagesize()));

	new = mmap(NULL,
		size,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE,
		-1,
		0);

	if (new == MAP_FAILED)
	{
		write(2, "MAP_FAILED\n", 11);
		return (NULL);
	}

	new->prev = NULL;
	if (g_zones.large)
		g_zones.large->prev = new;
	new->next = g_zones.large;
	g_zones.large = new;

	new->size = size - sizeof(t_elem_info);
	new->isfree = 0;
	new->addr = new + sizeof(t_elem_info);

	return (new->addr);
}

void		*malloc(size_t size)
{
	write(1, "m", 1); // debug
	return (large(size));
}