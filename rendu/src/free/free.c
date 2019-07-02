#include "free.h"

static void	free_large(t_elem_info *elem)
{
	if (elem->prev)
		elem->prev->next = elem->next;
	else
		g_lst.large = elem->net;
	if (elem->next)
		elem->next->prev = elem->prev;
	munmap(elem, elem->size + sizeof(t_elem_info));
}

static void	free_zone(t_type type, t_zone_info *zone)
{
	if (zone->next)
		zone->next->prev = zone->prev;
	if (zone->prev)
		zone->prev->next = zone->next;
	else
	{
		if (type == TINY)
			g_zones.tiny = zone->next;
		else
			g_zones.small = zone->next;
	}
	munmap(zone, zone->size);	
}

static void	free_other(t_elem_info *elem, const t_type type)
{
	elem->isfree = 1;
	while (elem->next && elem->next->isfree)
		merge(elem, elem->next);
	while (elem->prev && elem->prev->isfree)
	{
		elem = elem->prev;
		merge(elem, elem->next);
	}
	if (!(elem->prev) && !(elem->next))
		free_zone(type, (t_zone_info *)((void *)elem - sizeof(t_zone_info)));
}

static void	free_thread(void *ptr)
{
	t_elem_info	*elem;
	t_type		type;

	write(1, "\nf", 2); // debug
	if (!addr)
		write(2, "no addr to free\n", 16);
	else if (!(elem = identify(addr)))
		write(2, "invalid free\n", 13);
	else
	{
		if ((type = get_type(elem->size)) == LARGE)
			free_large(elem);
		else
			free_other(elem, type);
	}
}

void	free(void *ptr)
{
	if (pthread_mutex_lock(&g_mutex) != 0)
		return ;
	free_thread(ptr);
	pthread_mutex_unlock(&g_mutex);
}
