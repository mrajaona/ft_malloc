#include "free.h"

static void	free_large(t_elem_info *elem)
{
	write(1, "1", 1);

	if (!(elem->prev))
	{
		write(1, "a", 1);
		g_zones.large = elem->next;
		write(1, "b", 1);
	}
	else
	{
		write(1, "c", 1);
		elem->prev->next = elem->next;
		write(1, "d", 1);
	}

	write(1, "2", 1);

	if (elem->next)
		elem->next->prev = elem->prev;

	write(1, "3", 1);

	if (munmap(elem, elem->size + sizeof(t_elem_info)) < 0)
		write(2, "munmap failed\n", 14);

	write(1, "4", 1);
}

static t_elem_info	*find_elem(void *ptr)
{
	t_elem_info	*elem;

	// LARGE
	elem = g_zones.large;
	while (elem)
	{
		if (elem->addr == ptr)
			return (elem);
		elem = elem->next;
	}

	return (NULL);
}

void	free(void *ptr)
{
	t_elem_info	*elem;

	write(1, "f", 1);

	if (ptr == NULL)
		return ;

	if (!(elem = find_elem(ptr)))
	{
		write(1, "\nInvalid address\n", 17);
		return ;
	}

	elem->isfree = 1;
	free_large(elem);

	// todo : merge
	/*
	if (!(elem->prev) && !(elem->next))
		munmap(zone, zone size);
	*/
}