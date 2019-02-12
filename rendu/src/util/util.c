#include "ft_malloc_util.h"

size_t			align(size_t size)
{
	int			page_size;
	
	page_size = getpagesize();
	while (size % page_size)
		size++;
	return (size);
}

/**** identify ****/

static t_block_id	*find_id(t_block_id *lst, void *addr)
{
	t_block_id	*id;

	id = lst;
	while (id)
	{
		if (id->addr == addr)
			return (id);
		id = id->next;
	}
	return (NULL);
}

t_block_id			*identify(void *addr)
{
	t_block_id	*id;
	//t_zone_id	*zone;

	// check large
	if ((id = find_id(g_lst_large, addr)) != NULL)
		return (id);
	/*
	// check small
	zone = g_lst_small;
	while (zone)
	{
		if (zone->map_start <= addr && zone->map_end >= addr)
			if ((id = find_id(zone->lst_ids, addr)) != NULL)
				return (id);
		zone = zone->next;
	}
	// check tiny
	zone = g_lst_tiny;
	while (zone)
	{
		if (zone->map_start <= addr && zone->map_end >= addr)
			if ((id = find_id(zone->lst_ids, addr)) != NULL)
				return (id);
		zone = zone->next;
	}
	*/
	return (NULL);
}

