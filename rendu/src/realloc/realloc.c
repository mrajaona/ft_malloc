#include "ft_malloc_util.h"

static void	*ft_reallocate(void *addr, t_chunk_id *id, size_t size) // norme
{
	void		*ptr;

	if (
		(id->type == TINY && size < TINY_SIZE_MIN)
		|| (id->type == SMALL && size < SMALL_SIZE_MIN)
		|| (id->type == LARGE && size < LARGE_SIZE_MIN)
		)
	{
		if ((ptr = ft_malloc(size)) == NULL)
		{
			errno = ENOMEM;
			return (addr);
		}
		ft_memcpy(ptr, addr, size);
		ft_free(addr);
		return (ptr);		
	}
	else if (
		id->type != LARGE
		&& !(id->type == TINY && size > TINY_SIZE_MAX)
		&& !(id->type == SMALL && size > SMALL_SIZE_MAX)
		&& id->next->isfree == true
		&& (id->size + id->next->size) >= chunk_align(size)
	)
	{
		merge(id, id->next);
		split(id, size);
		return (addr);
	}
	else // (LARGE || size > MAX_SIZE || size < MIN_SIZE)
	{
		if ((ptr = ft_malloc(size)) == NULL)
		{
			errno = ENOMEM;
			return (addr);
		}
		ft_memcpy(ptr, addr, id->size);
		ft_free(addr);
		return (ptr);
	}
}

void		*ft_realloc(void *addr, size_t size)
{
	t_chunk_id	*id;
	size_t		aligned;

	if (!addr)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(addr);
		return (NULL);
	}
	if ((id = identify(addr)) == NULL)
	{
		return (NULL);
	}
	aligned = chunk_align(size);
	if (aligned == id->size)
	{
		return (addr);
	}
	else if (aligned < id->size)
	{
		split(id, size);
		ft_free(id->next);
		return (addr);
	}
	else
		return (ft_reallocate(addr, id, size));
}