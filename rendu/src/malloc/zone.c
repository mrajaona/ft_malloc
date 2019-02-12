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
	void		*ptr;
	size_t		size;

	if (type == TINY)
		size = getpagesize() * TINY_N_MAX * (sizeof(t_identifier) + TINY_SIZE_MAX);
	else // SMALL
		size = getpagesize() * SMALL_N_MAX * (sizeof(t_identifier) + SMALL_SIZE_MAX);
	size = zone_align(size);

	ptr = mmap(NULL, size, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET);
	id = (t_zone_id *)ptr;
	id->size = size + sizeof(t_zone_id);
	id->type = type;
	
	id->lst_alloc = NULL;

	id->lst_free = (t_identifier *)(ptr + sizeof(t_zone_id));
	id->lst_free->type = id->type;
	id->lst_free->size = id->size;
	id->lst_free->prev = NULL;
	id->lst_free->next = NULL;
	
	return(id);
}