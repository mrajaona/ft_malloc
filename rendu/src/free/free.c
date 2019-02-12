#include "ft_malloc.h"

// convert to free slot

// merge consectutive free slots

void	free(void *addr)
{
	t_block_id	*id;

	write(1, "f", 1);
	if (addr == NULL)
		return ;
	id = identify(addr);
	rm_id(id);
	// if (id->type == LARGE)
		munmap(id, id->size + sizeof(t_block_id));
		// munmap(id->addr, id->size);

	// update lst_alloc and lst_free
	// delete zone if necessary. update lst_tiny or lst_small.

}