#include "ft_malloc.h"

static void	*ft_realloc_large(void *src, size_t size)
{
	void			*addr;
	t_block_id		*id;
	t_block_id		*src_id;

	addr = malloc(size); // check NULL
	src_id = identify(src);
	ft_memcpy(addr, src, src_id->size);

	id = identify(addr);
	free(src);
	return (id->addr);
}

void	*realloc(void *addr, size_t size)
{
	write(1, "r", 1);
	if (addr == NULL)
		return (malloc(size));
	else //if (size > SMALL_MAX)
		return (ft_realloc_large(addr, size));
}