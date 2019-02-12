#include "ft_malloc_util.h"

void	*realloc(void *addr, size_t size)
{
	t_chunk_id	*id;
	void		*ptr;

	write(1, "r", 1);
	if (!addr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return ;
	}
	if ((id = identify(addr)) == NULL)
		return (NULL);
	if (id->type == LARGE)
	{
		if ((ptr = malloc(size)) == NULL)
		{
			errno = ENOMEM;
			return (addr);
		}
		ft_memcpy(ptr, addr, id->size);
		free(addr);
		return (ptr);
	}
	else
	{

	}
	return (NULL);
}