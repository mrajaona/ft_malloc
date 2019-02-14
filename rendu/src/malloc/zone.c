#include "ft_malloc_util.h"

static t_zone_id	*ft_create(const enum e_type type)
{
	t_zone_id	*zone;
	size_t		length;

	// create zone
	if (type == TINY)
		length = TINY_N * chunk_align(TINY_SIZE_MAX);
	else // SMALL
		length = SMALL_N * chunk_align(SMALL_SIZE_MAX);
	length = zone_align(length);

	if (
		(zone = (t_zone_id *)mmap(
			NULL, length, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET
		)) == MAP_FAILED
	)
	{
		errno = ENOMEM;
		return (NULL);
	}

	zone->size = length;
	zone->prev = NULL;
	zone->next = NULL;
	return (zone);
}

static void	ft_push(t_zone_id *zone, const enum e_type type) // norme
{
	t_zone_id	*cursor;
	
	// add to lst in order
	cursor = (type == TINY) ? g_lst.tiny : g_lst.small;
	if (!cursor)
	{
		if (type == TINY)
			g_lst.tiny = zone;
		else // SMALL
			g_lst.small = zone;
	}
	else
	{
		while (cursor->next && cursor < zone)
			cursor = cursor->next;
		if (cursor > zone)
		{
			zone->prev = cursor->prev;
			zone->next = cursor;
			cursor->prev = zone;
		}
		else // !cursor->next && cursor < id
		{
			cursor->next = zone;
			zone->prev = cursor;
		}
	}
}

t_zone_id	*create_zone(const enum e_type type)
{
	t_zone_id	*zone;
	t_chunk_id	*chunk;

	if ((zone = ft_create(type)) == NULL)
		return (NULL);
	ft_push(zone, type);
	// create single free chunk
	chunk = (t_chunk_id *)((char *)zone + sizeof(t_zone_id));
	chunk->type = type;
	chunk->addr = (char *)chunk + sizeof(t_chunk_id);
	chunk->size = zone->size - sizeof(t_zone_id);
	chunk->isfree = true;
	chunk->prev = NULL;
	chunk->next = NULL;
	return (zone);
}

t_chunk_id	*check_zone(t_zone_id *zone, size_t size)
{
	t_chunk_id	*cursor;
	t_chunk_id	*id;

	id = NULL;
	cursor = (t_chunk_id *)((char *)zone + sizeof(t_zone_id));
	size = chunk_align(size);
	while (cursor)
	{
		if (
			cursor->isfree == true
			&& cursor->size >= size
			&& (!id || id->size > cursor->size)
		)
			id = cursor;
		cursor = cursor->next;
	}
	return (id);
}