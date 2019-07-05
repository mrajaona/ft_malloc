#include "realloc.h"

#include "ft_printf.h" // debug

static void		*reallocate(t_elem_info *elem, size_t size)
{
	void		*ptr;
	t_elem_info	*new;

	if (!(ptr = malloc_thread(size)))
		return (elem->addr); // Check behaviour
	if (!(new = identify(ptr)))
		return (elem->addr); // ERROR

	ft_printf("addr : %p, size : %llu (%llu)\n", new->addr,
		new->size, new->size + sizeof(t_elem_info)); // debug

	ft_printf("t_elem_info : %llu\n", sizeof(t_elem_info));

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

	char *tab[] = {"TINY", "SMALL", "LARGE"}; // debug
	ft_printf("%s\t-> %s\n", tab[old_type], tab[new_type]); // debug

	if (old_type != LARGE && old_type == new_type)
	{
		split(elem, size);
		return (elem->addr);
	}
	else if (old_type == LARGE && old_type == new_type)
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
