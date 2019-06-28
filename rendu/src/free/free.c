#include "free.h"

// free

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

static void	free_other(t_elem_info *elem)
{
	t_zone_info	*zone;

	while (elem->prev && elem->prev->isfree)
		elem = merge(elem->prev, elem);
	while (elem->next && elem->next->isfree)
		elem = merge(elem, elem->next);

	if (!(elem->prev) && !(elem->next) && elem->isfree)
	{
		zone = (void *)elem - sizeof(t_zone_info);
		if (!(zone->prev))
		{
			if (zone->size >= SMALL_MIN)
				g_zones.small = zone->next;
			else
				g_zones.tiny = zone->next;
		}
		else
			zone->prev->next = zone->next;
		if (zone->next)
			zone->next->prev = zone->prev;
		if (munmap(zone, zone->size + sizeof(t_zone_info)) < 0)
			write(2, "munmap failed\n", 14);
	}
}

// main

void	free(void *ptr)
{
	t_elem_info	*elem;

	write(1, "f", 1); // debug
	if (ptr == NULL)
		return ;
	if (!(elem = identify(ptr)))
	{
		write(1, "\nInvalid address\n", 17);
		return ;
	}
	elem->isfree = 1;

	if (elem->size >= LARGE_MIN)
		free_large(elem);
	else
		free_other(elem);
}