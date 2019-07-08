/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:53:41 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:53:44 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_large.h"

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
	if (!(new->prev))
		g_zones.large = new;
}

void		*large(size_t size)
{
	t_elem_info	*new;

	size = size + sizeof(t_elem_info);
	size = size + (getpagesize() - (size % getpagesize()));
	if ((new = (t_elem_info *)mmap(NULL, size,
		MMAP_PROT,
		MMAP_FLAG,
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
