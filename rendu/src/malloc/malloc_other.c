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
	size_t		size;

	size = sizeof(t_zone_info) + ((ZONE_CAPACITY)
			* (sizeof(t_elem_info) + (type == TINY ? TINY_MAX : SMALL_MAX)));
	size = size + (getpagesize() - (size % getpagesize()));
	if ((new = (t_zone_info *)mmap(NULL, size,
		MMAP_PROT,
		MMAP_FLAG,
		-1, 0)) == MAP_FAILED)
	{
		errno = ENOMEM;
		return (NULL);
	}
	new->size = size - sizeof(t_zone_info);
	new->prev = NULL;
	new->next = NULL;
	new->first = (t_elem_info *)((char *)new + sizeof(t_zone_info));
	new->first->prev = NULL;
	new->first->next = NULL;
	new->first->size = new->size - sizeof(t_elem_info);
	new->first->isfree = 1;
	new->first->addr = (char *)(new->first) + sizeof(t_elem_info);
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

#include "ft_printf.h" // debug

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

	// debug
	ft_printf("%s\n\tzone %llu (%llu)\n\telem %llu (%llu)\n\taddr %llu (%llu)\n", type == TINY ? "tiny" : "small",
		(unsigned long long)cursor,
		(unsigned long long)cursor % 16,
		(unsigned long long)elem,
		(unsigned long long)elem % 16,
		(unsigned long long)(elem->addr),
		(unsigned long long)(elem->addr) % 16
	);

	split(elem, size);

	return (elem->addr);
}
