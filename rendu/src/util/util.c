#include "ft_malloc_util.h"
/*
t_chunk_id	*identify(void *addr)
{
	t_chunk_id	*id;

	if (!addr)
		return (NULL);
	id = (t_chunk_id *)((char *)addr - sizeof(t_chunk_id));
	if (id->addr != addr)
		return (NULL);
	return (id);
}
*/

static t_chunk_id  *id_find_in_zone(t_chunk_id *first, const void *addr)
{
	t_chunk_id *elem;

	elem = first;
	while (elem)
	{
		if (elem->addr == addr)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

static t_chunk_id  *id_check_zone(t_zone_id *zone, const void *addr)
{
	t_chunk_id	*first;

	first = (t_chunk_id *)((char *)zone + sizeof(t_zone_id));
	if (addr < first->addr
		|| addr > ((void *)zone + zone->size))
		return (NULL);
	return (id_find_in_zone(first, addr));
}

t_chunk_id         *identify(void *addr)
{
	t_zone_id	*zone;
	t_chunk_id	*elem;

	// TINY
	zone = g_lst.tiny;
	while (zone)
	{
		if (NULL != (elem = id_check_zone(zone, addr)))
			return (elem);
		zone = zone->next;
	}

	// SMALL
	zone = g_lst.small;
	while (zone)
	{
		if (NULL != (elem = id_check_zone(zone, addr)))
			return (elem);
		zone = zone->next;
	}

	// LARGE
	return (id_find_in_zone(g_lst.large, addr));
}
