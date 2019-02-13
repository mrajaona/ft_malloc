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
	/*
	if (aligned_size == id_size)
		return (addr);
	else if (aligned_size < id->size)
	{
		free(useless part);
	}
	*/
	else
	{
		if (
			id->type != LARGE
			&& id->next->isfree == NULL
			&& (id->size + id->next->size) > (size + sizeof(t_chunk_id))
		)
		{
			; // merge and split
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