#include "ft_malloc.h"

static t_block_id	*ft_malloc_large(size_t size)
{
	void		*addr;
	t_block_id	*id;
	size_t		aligned;

	aligned = align(size + sizeof(t_block_id));
	addr = mmap(NULL, aligned, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET); // check NULL

	id = add_id(LARGE, addr);
	id->size = aligned - sizeof(t_block_id);
	return (id);
}

/*
** allocate size + sizeof(t_block_id)
** sets identifier
** returns id.addr
*/
void	*malloc(size_t size)
{
	t_block_id			*id;
	/*
	static t_zone_id	*lst_tiny = NULL;
	static t_zone_id	*lst_small = NULL;
	static t_block_id	*lst_large = NULL;
	*/
	write(1, "m", 1);
	id = NULL;
	// if (size > SMALL_MAX)
		id = ft_malloc_large(size);
	// check id == NULL
	return (id->addr);
}