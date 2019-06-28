#include "malloc.h"

static void	push_large(t_elem_info *new)
{
	t_elem_info	*cursor;

	cursor = g_zones.large;
	if (!cursor)
	{
		new->prev = NULL;
		new->next = NULL;
		g_zones.large = new;
	}
	else
	{
		while (cursor->next && cursor->addr < new->addr)
			cursor = cursor->next;

		if (cursor->addr < new->addr)
		{
			new->next = cursor->next;
			new->prev = cursor;
			cursor->next = new;
		}
		else
		{
			new->next = cursor;
			new->prev = cursor->prev;
			cursor->prev = new;
		}

		if (new->next)
			new->next->prev = new;
		if (new->prev)
			new->prev->next = new;

		if (!(new->prev)) // first
			g_zones.large = new;

	}
}

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

	new->size = size - sizeof(t_elem_info);
	new->isfree = 0;
	new->addr = new + sizeof(t_elem_info);

	push_large(new);
	return (new->addr);
}

static void	push_zone(t_zone_info **list, t_zone_info *new)
{
	t_zone_info	*cursor;

	cursor = *list;

	if (!cursor)
	{
		new->prev = NULL;
		new->next = NULL;
		*list = new;
	}
	else
	{
		while (cursor->next && cursor->first < new->first)
			cursor = cursor->next;

		if (cursor->first < new->first)
		{
			new->next = cursor->next;
			new->prev = cursor;
			cursor->next = new;
		}
		else
		{
			new->next = cursor;
			new->prev = cursor->prev;
			cursor->prev = new;
		}

		if (new->next)
			new->next->prev = new;
		if (new->prev)
			new->prev->next = new;

		if (!(new->prev)) // first
			*list = new;
	}

	if (!(new->prev))
		*list = new;
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
		errno = ENOMEM;
		return (NULL);
	}

	new->size = size - sizeof(t_zone_info);
	new->first = (void *)new + sizeof(t_zone_info);

	new->first->size = new->size - sizeof(t_elem_info);
	new->first->isfree = 1;
	new->first->addr = (void *)(new->first) + sizeof(t_elem_info);
	new->first->prev = NULL;
	new->first->next = NULL;

	push_zone(list, new);

	return (new->first);
}

// todo : find smallest fitting
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
	t_elem_info	*free_elem;

	if (!(elem = find_free(size)))
		elem = create_zone(size >= SMALL_MIN ? SMALL : TINY);

	if (!elem)
		return (NULL);
	
	elem->isfree = 0;

	if ((elem->size - sizeof(t_zone_info)) <= (sizeof(t_zone_info)))
		return (elem->addr);

	free_elem = (void *)elem + sizeof(t_zone_info) + size;
	free_elem->isfree = 1;
	free_elem->size = elem->size - size - sizeof(t_zone_info);
	free_elem->addr = (void *)free_elem + sizeof(t_elem_info);
	free_elem->prev = elem;
	free_elem->next = elem->next;

	if (elem->next)
		elem->next->prev = free_elem;
	elem->size = size;
	elem->next = free_elem;

	return (elem->addr);
}

void		*malloc(size_t size)
{
	write(1, "m", 1); // debug

	if (size >= LARGE_MIN)
		write(1, "L", 1);
	else if (size >= SMALL_MIN)
		write(1, "S", 1);
	else
		write(1, "T", 1);

	if (size >= LARGE_MIN)
		return (large(size));
	else
		return (other(size));
}
