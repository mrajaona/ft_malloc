#include "realloc.h"

static void		*reallocate(t_elem_info *elem, size_t size)
{
	void		*ptr;
	t_elem_info	*new;

	if (!(ptr = malloc(size)))
		return (elem->addr); // Check behaviour
	if (!(new = identify(ptr)))
		return (elem->addr); // ERROR
	ft_memcpy(ptr, elem->addr, (size < elem->size ? size : elem->size));
	free(elem->addr);
	return (ptr);
}

static void		*realloc_less(t_elem_info *elem, size_t size)
{
	t_type	type;
	size_t	l_size;

	type = get_type(elem->size);
	if (type != LARGE && type == get_type(size))
	{
		split(elem, size);
		return (elem->addr);
	}
	else if (type == LARGE)
	{
		l_size = size + sizeof(t_elem_info);
		l_size = l_size + (getpagesize() - (l_size % getpagesize()));
		if (l_size == elem->size + sizeof(t_elem_info))
			return (elem->addr);
		else
			return (reallocate(elem, size));
	}
	else
		return (reallocate(elem, size));
}

static void		*realloc_more(t_elem_info *elem, size_t size)
{
	if (get_type(elem->size) == get_type(size))
	{
		if (elem->next && elem->next->isfree
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

static void		*realloc_thread(void *ptr, size_t size)
{
	t_elem_info	*elem;

	if (!ptr)
		return (malloc(size));
	else if (!(elem = identify(ptr)))
		return (NULL);
	else if (size == 0) // Check behaviour
	{
		free(ptr);
		return (NULL);
	}
	else if (size == elem->size)
		return (elem->addr);
	else if (size < elem->size)
		return (realloc_less(elem, size));
	else // (size > elem->size)
		return (realloc_more(elem, size));	
}

void			*realloc(void *ptr, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (ptr); // Check behaviour
	ret = realloc_thread(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
