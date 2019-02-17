#include "ft_malloc_util.h"

t_list	g_lst = {NULL, NULL, NULL};

static void	*ft_malloc_small(const size_t size, const enum e_type type)
{
	t_chunk_id	*id;
	t_zone_id	*cursor;

	cursor = (type == TINY) ? g_lst.tiny : g_lst.small;
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

static void	ft_push_large(t_chunk_id *id)
{
	t_chunk_id	*cursor;

	cursor = g_lst.large;
	if (!cursor)
		g_lst.large = id;
	else
	{
		while (cursor->next && cursor->addr < id->addr)
			cursor = cursor->next;

		if (cursor->addr < id->addr)
		{
			id->next = cursor->next;
			id->prev = cursor;
		}
		else
		{
			id->next = cursor;
			id->prev = cursor->prev;
		}

		if (id->next)
			id->next->prev = id;
		if (id->prev)
			id->prev->next = id;

		if (!(id->prev)) // first
			g_lst.large = id;
	}
}

static void	*ft_malloc_large(const size_t size)
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
	id->prev = NULL;
	id->next = NULL;
	ft_push_large(id);
	return (id->addr);
}

void	*ft_malloc(size_t size)
{
	if (size <= TINY_SIZE_MAX)
		return (ft_malloc_small(size, TINY));
	else if (size <= SMALL_SIZE_MAX)
		return (ft_malloc_small(size, SMALL));
	else
		return (ft_malloc_large(size));
}