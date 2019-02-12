#include "ft_malloc.h"

t_zone_id	*create_zone(enum e_type type)
{
	t_zone_id	*id;
	size_t		n_min;
	size_t		size;

	if (type == TINY)
	{
		n_min = TINY_N;
		size = TINY_SIZE_MAX;
	}
	else // small
	{
		n_min = SMALL_N;
		size = SMALL_SIZE_MAX;
	}

	size = getpagesize() * n_min * size;
	size = align(size + sizeof(t_zone_id));

	id = (t_zone_id *)mmap(NULL, size, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET); // check NULL

	id->size = size - sizeof(t_zone_id);
	id->lst_alloc = NULL;
	id->lst_free = NULL;

	return(id);
}