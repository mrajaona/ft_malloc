#include "ft_malloc_util.h"

void	*realloc(void *addr, size_t size)
{
	t_block_id	*id;
	void		*ptr;

	write(1, "r", 1);
	if (!addr)
		return (malloc(size));
	if ((id = identify(addr)) == NULL)
		return (NULL);
	if (id->type == LARGE)
	{
		if ((ptr = malloc(size)) == NULL)
		{
			// error
			return (addr);
		}
		ft_memcpy(ptr, addr, id->size);
		free(addr);
		return (ptr);
	}
	return (NULL);
}