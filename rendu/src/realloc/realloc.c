#include "ft_malloc_util.h"

void	*realloc(void *addr, size_t size)
{
	t_chunk_id	*id;
	void		*ptr;
	size_t		aligned;

	write(1, "\nr", 2);
	if (!addr)
		return (malloc(size));
	if (size == 0)
	{
		free(addr);
		return (NULL);
	}
	if ((id = identify(addr)) == NULL)
		return (NULL);
	aligned = chunk_align(size);
	if (aligned == id->size)
		return (addr);
	else if (aligned < id->size)
	{
		split(id, size);
		free(id->next);
		return (addr);
	}
	else
	{
		if (
			id->type != LARGE
			&& id->next->isfree == true
			&& (id->size + id->next->size) >= aligned
		)
		{
			merge(id, id->next);
			split(id, size);
			return (addr);
		}
		else
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
	}
	return (NULL);
}