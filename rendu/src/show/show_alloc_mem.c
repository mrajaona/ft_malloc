#include "show_alloc_mem.h"

// SHOW SUB

static void	show_elem(t_elem_info *elem, unsigned long long *total)
{
	ft_printf("%p - %p : \n",
		elem->addr,
		elem->addr + elem->size - 1,
		elem->size
		);
	*total += elem->size; // TODO
}

static void	show_zone(t_zone_info *zone, unsigned long long *total)
{
	t_elem_info	*cursor;

	cursor = zone->first;
	while (cursor)
	{
		if (!(cursor->isfree))
			show_elem(cursor, total);
		cursor = cursor->next;
	}
}

// SHOW

static void	show_tiny(t_zone_info *zone, unsigned long long *total)
{
	ft_printf("%s : %p\n", "TINY", zone);
	show_zone(zone, total);
}

static void	show_small(t_zone_info *zone, unsigned long long *total)
{
	ft_printf("%s : %p\n", "SMALL", zone);
	show_zone(zone, total);
}

static void	show_large(t_elem_info *elem, unsigned long long *total)
{
	ft_printf("%s : %p\n", "LARGE", elem);
	show_elem(elem, total);
}

// INIT

static void	*get_first(void *a, void *b, void *c)
{
	void	*first;

	first = a;
	if (!first || (b && b < first))
		first = b;
	if (!first || (c && c < first))
		first = c;
	return (first);
}

void    show_alloc_mem(void)
{
	t_zones				zones;
	void				*first;
	unsigned long long	total;

	zones = g_zones;
	total = 0;
	while (zones.tiny || zones.small || zones.large)
	{
		if (!(first = get_first(zones.tiny, zones.small, zones.large)))
			break ; // check norme
		if (first == (void *)(zones.tiny))
		{
			show_tiny(zones.tiny, &total);
			zones.tiny = zones.tiny->next;
		}
		else if (first == (void *)(zones.small))
		{
			show_small(zones.small, &total);
			zones.small = zones.small->next;
		}
		else if (first == (void *)(zones.large))
		{
			show_large(zones.large, &total);
			zones.large = zones.large->next;
		}
		else
			write(2, "Error : unkown allocation.\n", 27);
	}
	ft_printf("Total : %llu\n", total);
}