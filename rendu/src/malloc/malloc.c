#include "ft_malloc_util.h"

t_list	g_lst = {NULL, NULL, NULL};

static void	*ft_malloc(size_t size, enum e_type type)
{
	t_chunk_id	*id;
	t_zone_id	*cursor;

	cursor = type == TINY ? g_lst.tiny : g_lst.small;
	// cursor can be NULL at this point
	id = NULL;
	while (cursor && !id)
	{
		id = check_zone(cursor, size);
		cursor = cursor->next;
	}
	if (!id) // need new zone
	{
		if ((cursor = create_zone(type)) == NULL)
			return (NULL);
		id = (t_chunk_id *)((char *)cursor + sizeof(t_zone_id));
	}
	split(id, size);
	return (id->addr);
}

static void	*ft_malloc_large(size_t size)
{
	size_t		length;
	t_chunk_id	*id;
	
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
	id->addr = (char *)id + sizeof(t_chunk_id);

	id->size = length;
	id->isfree = false;

	// add to g_lst.large start
	// order does not matter here
	id->prev = NULL;
	id->next = g_lst.large;
	if (g_lst.large)
		g_lst.large->prev = id;
	g_lst.large = id;

	return (id->addr);
}

void	*malloc(size_t size)
{
	; // write(1, "\nm", 2);

	if (size <= TINY_SIZE_MAX)
	{
		; // write(1, "T", 1);
		return (ft_malloc(size, TINY));
	}
	else if (size <= SMALL_SIZE_MAX)
	{
		; // write(1, "S", 1);
		return (ft_malloc(size, SMALL));
	}
	else
	{
		; // write(1, "L", 1);
		return (ft_malloc_large(size));
	}
}