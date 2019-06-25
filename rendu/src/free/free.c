#include "free.h"

static void	free_large(t_elem_info *elem)
{
	if (!(elem->prev))
		g_zones.large = elem->next;
	else
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	if (munmap(elem, elem->size + sizeof(t_elem_info)) < 0)
		write(2, "munmap failed\n", 14);
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

	write(1, "f", 1); // debug
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