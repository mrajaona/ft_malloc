#include "ft_malloc_util.h"

// convert to free slot

// merge consecutive free slots
static void	merge(t_block_id *first, t_block_id *second)
{
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	first->size = first->size + second->size;

	second->addr = NULL;
	second->size = 0;
	second->isfree = true;
	second->prev = NULL;
	second->next = NULL;
}


void	free(void *addr)
{
	t_block_id	*id;

	write(1, "f", 1);
	if (!addr)
		return ;
	if ((id = identify(addr)) == NULL)
		return ;
	if (id->type != LARGE)
	{
		id->isfree = true;
		if (id->next && id->next->isfree == false)
			merge(id, id->next);
		// check empty list
		//	munmap empty list
	}
	else // if (id->type == LARGE)
	{
		if (id->next)
			id->next->prev = id->prev;
		if (id->prev)
			id->prev->next = id->next;
		else
			g_lst_large = id->next;
		munmap(id, id->size + sizeof(t_block_id));
	}
}