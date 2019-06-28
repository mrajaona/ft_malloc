#include "realloc.h"

static void	*reallocate(t_elem_info *elem, size_t size)
{
	(void)elem;
	(void)size;
	return (elem->addr);
}

void		*realloc(void *ptr, size_t size)
{
	t_elem_info	*elem;
	t_elem_info	*tmp;

    write(1, "r", 1); // debug
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
	else if (size < elem->size)
	{
		elem->size = size;

		tmp = (void *)elem + sizeof(t_zone_info) + size;
		tmp->isfree = 1;
		tmp->size = elem->size - size - sizeof(t_zone_info);
		tmp->addr = (void *)tmp + sizeof(t_elem_info);
		tmp->prev = elem;
		tmp->next = elem->next;

		if (elem->next)
			elem->next->prev = tmp;
		elem->size = size;
		elem->next = tmp;

		if (elem->next)
		{
			tmp = elem->next;
			while (tmp->next && tmp->next->isfree)
				tmp = merge(tmp, tmp->next);
		}
		return (elem->addr);
	}
	else
		return (reallocate(elem, size));
}
