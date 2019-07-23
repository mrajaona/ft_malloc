/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:18 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:19 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "realloc.h"

static void		*reallocate(t_elem_info *elem, size_t size)
{
	void		*ptr;
	t_elem_info	*new;

	if (!(ptr = malloc_thread(size)))
		return (NULL);
	if (!(new = identify(ptr)))
		return (NULL);
	ft_memcpy(ptr, elem->addr, (size < elem->size ? size : elem->size));
	free_thread(elem->addr);
	return (ptr);
}

static void		*realloc_less(t_elem_info *elem, size_t size)
{
	t_type	old_type;
	t_type	new_type;
	size_t	l_size;

	old_type = get_type(elem->size);
	new_type = get_type(size);
	if (old_type == new_type)
	{
		if (old_type != LARGE)
		{
			split(elem, size);
			return (elem->addr);
		}
		else
		{
			l_size = size + sizeof(t_elem_info);
			l_size = l_size + (getpagesize() - (l_size % getpagesize()));
			if (l_size == elem->size + sizeof(t_elem_info))
				return (elem->addr);
			else
				return (reallocate(elem, size));
		}
	}
	else
		return (reallocate(elem, size));
}

static void		*realloc_more(t_elem_info *elem, size_t size)
{
	t_type	old_type;
	t_type	new_type;

	old_type = get_type(elem->size);
	new_type = get_type(size);
	if (old_type == new_type)
	{
		if (old_type == LARGE)
			return (reallocate(elem, size));
		else if (elem->next && elem->next->isfree
			&& elem->size + sizeof(t_elem_info) + elem->next->size >= size)
		{
			merge(elem, elem->next);
			split(elem, size);
			return (elem->addr);
		}
		else
			return (reallocate(elem, size));
	}
	else
		return (reallocate(elem, size));
}

void			*realloc_thread(void *ptr, size_t size)
{
	t_elem_info	*elem;

	if (!ptr)
		return (malloc_thread(size));
	else if (!(elem = identify(ptr)))
		return (NULL);
	else if (size == 0)
	{
		free_thread(ptr);
		return (malloc_thread(0));
	}
	else
	{
		size = malloc_check_size(size);
		if (size == elem->size)
			return (elem->addr);
		else if (size < elem->size)
			return (realloc_less(elem, size));
		else
			return (realloc_more(elem, size));
	}
}

void			*realloc(void *ptr, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	ret = realloc_thread(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
