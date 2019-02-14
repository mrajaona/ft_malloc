#include "ft_malloc_util.h"

/*
** struct size is aligned with biggest type in struct
** so the beggining of zone and chunk should be aligned
*/
size_t		chunk_align(size_t size)
{
	size_t	aligned;

	aligned = size + sizeof(t_chunk_id);
	while (aligned % 64)
		aligned++;
	return (aligned);
}

size_t		zone_align(size_t size)
{
	size_t	aligned;

	aligned = size + sizeof(t_zone_id);
	while (aligned % 64)
		aligned++;
	return (aligned);
}

size_t		mmap_align(size_t size)
{
	int			page_size;
	
	page_size = getpagesize();
	while (size % page_size)
		size++;
	return (size);
}
