#include "ft_malloc.h"

size_t		zone_align(size_t size)
{
	int		page_size;
	size_t	full;
	
	page_size = getpagesize();
	full = size + sizeof(t_zone_id);
	while (full % page_size)
		full++;
	return (full);
}

t_zone_id	*create_zone(enum e_page type)
{
	t_zone_id	*id;
	void	*ptr;
	size_t	size;

	if (type == TINY)
		size = getpagesize() * 100 * (sizeof(t_identifier) + TINY_MAX);
	else // SMALL
		size = getpagesize() * 100 * (sizeof(t_identifier) + SMALL_MAX);
	size = zone_align(size);
	ptr = mmap(NULL, size, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET);
	id = (t_zone_id *)ptr;
	id->size = size;
	id->type = type;
	id->first = NULL;
	return(id);
}