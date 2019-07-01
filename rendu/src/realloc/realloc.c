#include "realloc.h"

static t_type	get_type(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	else if (size <= SMALL_MAX)
		return (SMALL);
	else
		return (LARGE);
}

static void		cpy_mem(void *old_ptr, size_t old_size,
	void *new_ptr, size_t new_size)
{
	if (old_ptr && new_ptr)
		ft_memcpy(new_ptr, old_ptr, new_size < old_size ? new_size : old_size);
	free(old_ptr);
}

static void		*new_alloc(t_elem_info *elem, size_t size)
{
	void		*new_ptr;
	t_elem_info	*new_elem;

	new_ptr = malloc(size);
	if (new_ptr)
	{
		new_elem = identify(new_ptr);
		size = new_elem ? new_elem->size : 0;
	}
	cpy_mem(elem->addr, elem->size, new_ptr, size);
	return (new_ptr);	
}

static void		split(t_elem_info *elem, size_t size)
{
	t_elem_info	*free_elem;

	if (!elem || elem->size < size
		|| (elem->size - size) <= (sizeof(t_zone_info)))
		return ;
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

	if (elem->next)
	{
		free_elem = elem->next;
		while (free_elem->next && free_elem->next->isfree)
			free_elem = merge(free_elem, free_elem->next);
	}
}

static void		*reallocate(t_elem_info *elem, size_t size)
{
	t_type		cur_type;
	t_type		new_type;

	cur_type = get_type(elem->size);
	new_type = get_type(size);
	if (cur_type != new_type)
		return (new_alloc(elem, size));
	else if (size > elem->size)
	{
		if (elem->next
			&& elem->next->isfree
			&& (elem->size + sizeof(t_elem_info) + elem->next->size) >= size)
		{
			merge(elem, elem->next);
			if ((elem->size - size) <= (sizeof(t_zone_info)))
				return (elem->addr);
			split(elem, size);
			return (elem->addr);
		}
		else
			return (new_alloc(elem, size));
	}
	else if (size < elem->size)
	{
		split(elem, size);
		return (elem->addr);
	}
	return (elem->addr);
}

void			*realloc(void *ptr, size_t size)
{
	t_elem_info	*elem;

    write(1, "\nr", 2); // debug
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!(elem = identify(ptr)))
		return (NULL);
	if (size == elem->size)
		return (elem->addr);
	else
		return (reallocate(elem, size));
}
