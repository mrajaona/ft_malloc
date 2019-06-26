#include "malloc.h"

// add to start of list
static void	*large(size_t size)
{
	t_elem_info	*new;
	
	size = size + sizeof(t_elem_info);
	size = size + (getpagesize() - (size % getpagesize()));

	new = mmap(NULL,
		size,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE,
		-1,
		0);

	if (new == MAP_FAILED)
	{
		write(2, "MAP_FAILED\n", 11);
		return (NULL);
	}

	new->prev = NULL;
	if (g_zones.large)
		g_zones.large->prev = new;
	new->next = g_zones.large;
	g_zones.large = new;

	new->size = size - sizeof(t_elem_info);
	new->isfree = 0;
	new->addr = new + sizeof(t_elem_info);

	return (new->addr);
}

// zone_size % getpagesize == 0
static size_t	calc_zone_size(t_type type)
{
	int		zone_size;

	if (type == LARGE)
		return (0);
	else
		zone_size = ZONE_CAPACITY * (type == TINY ? TINY_MAX : SMALL_MAX);
	zone_size += sizeof(t_zone_info);
	zone_size += (getpagesize() - (zone_size % getpagesize()));
	return (zone_size);
}

static t_elem_info	*create_zone(t_type type)
{
	t_zone_info	*new;
	t_zone_info	**list;
	size_t		size;

	size = calc_zone_size(type);
	list = type == TINY ? &(g_zones.tiny) : &(g_zones.small);

	new = mmap(NULL,
		size,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE,
		-1,
		0);

	if (new == MAP_FAILED)
	{
		write(2, "MAP_FAILED\n", 11);
		return (NULL);
	}

	new->prev = NULL;
	if (*list)
		(*list)->prev = new;
	new->next = *list;
	*list = new;

	new->size = size - sizeof(t_zone_info);
	new->first = (void *)new + sizeof(t_zone_info);

	new->first->size = new->size - sizeof(t_elem_info);
	new->first->isfree = 1;
	new->first->addr = (void *)(new->first) + sizeof(t_elem_info);

	return (new->first->addr);
}

static t_elem_info	*find_in_zone(t_elem_info *first, size_t size)
{
	t_elem_info	*elem;

	elem = first;
	while (elem)
	{
		if (elem->isfree && elem->size >= size)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

static t_elem_info	*find_free(size_t size)
{
	t_zone_info	*zone;
	t_elem_info	*elem;

	zone = size >= SMALL_MIN ? g_zones.small : g_zones.tiny;
	while (zone)
	{
		if (NULL != (elem = find_in_zone(zone->first, size)))
			return (elem);
		zone = zone->next;
	}
	return (NULL);
}

static void	*other(size_t size)
{
	t_elem_info	*elem;
	if (!(elem = find_free(size)))
		elem = create_zone(size >= SMALL_MIN ? SMALL : TINY);

	if (!elem)
	{
		// ENOMEM
		return (NULL);
	}
	// todo : split

	return (NULL);
}

void		*malloc(size_t size)
{
	write(1, "m", 1); // debug

	if (size >= LARGE_MIN)
		return (large(size));
	else
		return (other(size));
}