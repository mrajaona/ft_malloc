#include "free.h"

static void	free_large(t_elem_info *elem)
{
	if (!(elem->prev))
		g_zones.large = elem->next;
	else
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	if (munmap(elem, elem->size + sizeof(t_elem_info)) < 0)
		write(2, "munmap failed\n", 14);
}

static t_elem_info	*find_in_zone(t_elem_info *first, const void *ptr)
{
	t_elem_info	*elem;

	elem = first;
	while (elem)
	{
		if (elem->addr == ptr)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

static t_elem_info	*find_elem(const void *ptr)
{
	t_zone_info	*zone;
	t_elem_info	*elem;

	// TINY
	zone = g_zones.tiny;
	while (zone)
	{
		if (NULL != (elem = find_in_zone(zone->first, ptr)))
			return (elem);
		zone = zone->next;
	}

	// SMALL
	zone = g_zones.small;
	while (zone)
	{
		if (NULL != (elem = find_in_zone(zone->first, ptr)))
			return (elem);
		zone = zone->next;
	}

	// LARGE
	return (find_in_zone(g_zones.large, ptr));
}

void	free(void *ptr)
{
	t_elem_info	*elem;

	write(1, "f", 1); // debug
	if (ptr == NULL)
		return ;
	if (!(elem = find_elem(ptr)))
	{
		write(1, "\nInvalid address\n", 17);
		return ;
	}
	elem->isfree = 1;
	free_large(elem);

	// todo : merge
	/*
	if (!(elem->prev) && !(elem->next))
		munmap(zone, zone size);
	*/
}