/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:53:52 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:53:52 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_other.h"

static void			insert_zone(t_zone_info *new, t_zone_info **list)
{
	t_zone_info	*cursor;

	cursor = *list;
	while (cursor->next && cursor < new)
		cursor = cursor->next;
	if (cursor < new)
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
	if (!(new->prev))
		*list = new;
}

static void			push_zone(t_zone_info *new, t_type type)
{
	t_zone_info	**list;

	list = type == TINY ? &(g_zones.tiny) : &(g_zones.small);
	if (!(*list))
	{
		new->prev = NULL;
		new->next = NULL;
		*list = new;
	}
	else
		insert_zone(new, list);
}

static t_zone_info	*create_zone(t_type type)
{
	t_zone_info	*new;
	t_elem_info	*first;
	size_t		size;

	size = sizeof(t_zone_info) + ((ZONE_CAPACITY)
			* (sizeof(t_elem_info) + (type == TINY ? TINY_MAX : SMALL_MAX)));
	size = size + (getpagesize() - (size % getpagesize()));
	if ((new = (t_zone_info *)mmap(NULL, size,
			MMAP_PROT, MMAP_FLAG, -1, 0)) == MAP_FAILED)
	{
		errno = ENOMEM;
		return (NULL);
	}
	new->size = size - sizeof(t_zone_info);
	new->prev = NULL;
	new->next = NULL;
	new->first = (t_elem_info *)((void *)new + sizeof(t_zone_info));
	first = new->first;
	first->prev = NULL;
	first->next = NULL;
	first->size = new->size - sizeof(t_elem_info);
	first->isfree = 1;
	first->addr = (void *)(first) + sizeof(t_elem_info);
	push_zone(new, type);
	return (new);
}

static void			chk_zone(t_elem_info **current, t_zone_info *zone,
	size_t size)
{
	t_elem_info	*cursor;

	cursor = zone->first;
	while (cursor)
	{
		if (cursor->isfree && cursor->size >= size
			&& (!(*current) || cursor->size < (*current)->size))
			*current = cursor;
		cursor = cursor->next;
	}
}

void				*other(size_t size, const t_type type)
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
			return (NULL);
		elem = cursor->first;
	}
	split(elem, size);
	return (elem->addr);
}
