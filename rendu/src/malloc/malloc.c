#include "ft_malloc_util.h"

t_list	g_lst = {NULL, NULL, NULL};

static void	*ft_malloc(const size_t size, const enum e_type type)
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
	id->prev = NULL;
	id->next = NULL;
	if (!cursor)
		g_lst.large = id;
	else
	{
		while (cursor->next && cursor->addr < id->addr)
			cursor = cursor->next;
		if (cursor->addr > id->addr)
		{
			id->prev = cursor->prev;
			id->next = cursor;
			cursor->prev = id;
		}
		else // !cursor->next && cursor->addr < id->addr
		{
			id->next = cursor;
			id->prev = cursor;
			cursor->next = id;
		}
		if (id->prev == NULL)
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
	ft_push_large(id);
	return (id->addr);
}

void	*malloc(size_t size)
{
	if (size <= TINY_SIZE_MAX)
		return (ft_malloc(size, TINY));
	else if (size <= SMALL_SIZE_MAX)
		return (ft_malloc(size, SMALL));
	else
		return (ft_malloc_large(size));
}