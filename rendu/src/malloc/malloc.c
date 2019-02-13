#include "ft_malloc_util.h"

t_zone_id	*g_lst_tiny = NULL;
t_zone_id	*g_lst_small = NULL;
t_chunk_id	*g_lst_large = NULL;

/*
static void	*ft_malloc(size_t size, enum e_type type)
{
	t_chunk_id	*id;
	t_zone_id	*cursor;

	cursor = type == TINY ? g_lst_tiny : g_lst_small;
	// cursor can be NULL at this point
	id = NULL;
	while (cursor && !id)
	{
		write(1, "\nz", 2);
		id = check_zone(cursor, size);
		cursor = cursor->next;
	}
	if (!id) // need new zone
	{
		write(1, "?", 2);
		if ((cursor = create_zone(type)) == NULL)
			return (NULL);
		id = (t_chunk_id *)(cursor + sizeof(t_zone_id));
	}
	else
		write(1, "!", 2);

	split(id, size);
	return (id);
}
*/
static void	*ft_malloc_large(size_t size)
{
	size_t		length;
	t_chunk_id	*id;
	
	write(1, "_", 1);
	length = mmap_align(chunk_align(size));
	if (
		(id = (t_chunk_id *)mmap(
			NULL, length, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET
		)) == MAP_FAILED
	)
	{
		errno = ENOMEM;
		return (NULL);
	}

	id->type = LARGE;
	id->addr = (void *)id + sizeof(t_chunk_id) * 8;

	if (id->addr - sizeof(t_chunk_id) * 8 != (void *)id)
		write(1, "\ngne\n", 5);

	id->size = length;
	id->isfree = false;

	// add to g_lst_large start
	// order does not matter here
	id->prev = NULL;
	id->next = g_lst_large;
	g_lst_large = id;

	return (!id ? NULL : id->addr);
}

void	*malloc(size_t size)
{
	write(1, "\nm", 2);
	/*************************
	if (size <= TINY_SIZE_MAX)
		return (ft_malloc(size, TINY));
	else if (size <= SMALL_SIZE_MAX)
		return (ft_malloc(size, SMALL));
	else
	************************/
		return (ft_malloc_large(size));
}