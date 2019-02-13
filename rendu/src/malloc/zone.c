#include "ft_malloc_util.h"

t_zone_id	*create_zone(enum e_type type)
{
	t_zone_id	*cursor;
	t_zone_id	*z_id;
	t_chunk_id	*c_id;
	size_t		length;

	(void)type;
	// create zone
	if (type == TINY)
		length = TINY_N * chunk_align(TINY_SIZE_MAX);
	else // SMALL
		length = SMALL_N * chunk_align(SMALL_SIZE_MAX);

	if (
		(z_id = (t_zone_id *)mmap(
			NULL, length, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET
		)) == MAP_FAILED
	)
	{
		errno = ENOMEM;
		return (NULL);
	}

	// create single free chunk
	c_id = (t_chunk_id *)(z_id + sizeof(t_zone_id));
	c_id->type = type;
	c_id->addr = c_id + sizeof(t_chunk_id);
	c_id->size = length - sizeof(t_zone_id);
	c_id->isfree = true;
	c_id->prev = NULL;
	c_id->next = NULL;

	// add to lst end
	// order is important here
	if (type == TINY)
		cursor = g_lst_tiny;
	else // SMALL
		cursor = g_lst_small;

	if (!cursor)
	{
		if (type == TINY)
			g_lst_tiny = z_id;
		else // SMALL
			g_lst_small = z_id;
	}
	else
	{
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = z_id;
		z_id->prev = cursor;
	}

	return (NULL);
}

t_chunk_id	*check_zone(t_zone_id *zone, size_t size)
{
	t_chunk_id	*id;

	id = (t_chunk_id *)(zone + sizeof(t_zone_id));
	size = chunk_align(size);
	while (id)
	{
		if (id->isfree == true && id->size >= size)
			return (id);
		id = id->next;
	}
	return (NULL);
}