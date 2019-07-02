#include "malloc.h"

// TINY - SMALL

static t_zone_info	*create_zone(t_type type)
{
	t_zone_info	*list;
	t_zone_info	*new;

	list = type == TINY ? g_zones.tiny : g_zones.small;

	// TODO
	new = NULL;

	return (new);
}

static void	chk_zone(t_elem_info **current, t_zone_info *zone, size_t size)
{
	t_elem_info	*cursor;

	cursor = zone->first;
	while (cursor)
	{
		if (cursor->size >= size
			&& (!(*current) || cursor->size < (*current)->size))
			*current = cursor;
		cursor = cursor->next;
	}
}

static void	*other(size_t size, const t_type type)
{
	t_zone_info	*cursor;
	t_elem_info	*elem;

	cursor = type == TINY ? g_zones.tiny : g_zones.small;
	elem = NULL;
	while (cursor)
	{
		chk_zone(&elem, cursor, size);
		cursor = cursor->next;		
	}
	if (!elem)
	{
		if (!(cursor = create_zone(type)))
			return (NULL); // ENOMEM
		elem = cursor->first;
	}
	split(elem, size);
	return (elem->addr);
}

// LARGE

static void	push_large(t_elem_info *new)
{
	t_elem_info	*cursor;

	cursor = g_zones.large;
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

static void	*large(size_t size)
{
	t_elem_info	*new;

	size = size + sizeof(t_elem_info);
	size = size + (getpagesize() - (size % getpagesize()));
	if ((new = (t_elem_info *)mmap(NULL, size,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANONYMOUS | MAP_PRIVATE,
		-1, 0)) == MAP_FAILED)
	{
		write(2, "MAP_FAILED\n", 11);
		return (NULL);
	}
	new->size = size - sizeof(t_elem_info);
	new->isfree = 0;
	new->addr = new + sizeof(t_elem_info);
	if (!(g_zones.large))
	{
		new->prev = NULL;
		new->next = NULL;
		g_zones.large = new;
	}
	else
		push_large(new);
	return (new->addr);
}

// MAIN

static void	*malloc_thread(size_t size)
{
	t_type	type;

	write(1, "\nm", 2); // debug
	if (size == 0)
		return (NULL);
	type = get_type(size);
	if (type == LARGE)
		return (large(size));
	else
		return (other(size, type));
	return (NULL);
}

void		*malloc(size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	ret = malloc_thread(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
