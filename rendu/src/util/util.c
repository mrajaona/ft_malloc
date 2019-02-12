#include "ft_malloc.h"

size_t			align(size_t size)
{
	int			page_size;
	
	page_size = getpagesize();
	while (size % page_size)
		size++;
	return (size);
}

t_block_id		*identify(void *addr)
{
	// check large
	// check small
	// check tiny
	return ((t_block_id *)(addr - sizeof(t_block_id)));
}

t_block_id		*add_id(enum e_type type, void *addr)
{
	t_block_id	*id;

	id = (t_block_id *)(addr);

	id->type = type;
	id->addr = addr + sizeof(t_block_id);

	id->prev = NULL;
	id->next = NULL;

	return (id);
}

void			rm_id(t_block_id *id)
{
	if (id->prev != NULL)
		id->prev->next = id->next;
	else
	{
		// update lst
	}
	if (id->next != NULL)
		id->next->prev = id->prev;
}