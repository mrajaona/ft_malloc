#include "ft_malloc_util.h"

t_zone_id	*g_lst_tiny = NULL;
t_zone_id	*g_lst_small = NULL;
t_chunk_id	*g_lst_large = NULL;

static t_chunk_id	*check_zone(t_zone_id *zone, size_t size)
{
	t_chunk_id	*id;

	id = zone->lst_ids;
	while (id)
	{
		if (id->isfree == true && id->size >= size)
			return (id);
		id = id->next;
	}
	return (NULL);
}

static void	*ft_malloc(size_t size, enum e_type type, t_zone_id *lst)
{
	return (NULL);
}

static void	*ft_malloc_large(size_t size)
{
	size_t		length;
	t_chunk_id	*id;
	
	length = align(size + sizeof(t_chunk_id));
	if (
		(id = (t_chunk_id *)mmap(
			NULL, length, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET
		)) == MAP_FAILED
	)
	{
		errno = ENOMEM;
		return (NULL);
	}

	id->type = LARGE;
	id->addr = id + sizeof(t_chunk_id);
	id->size = length;
	id->isfree = false;

	id->prev = NULL;
	id->next = g_lst_large;
	g_lst_large = id;

	return (id == NULL ? NULL : id->addr);
}

void	*malloc(size_t size)
{
	write(1, "m", 1);
	if (size <= TINY_SIZE_MAX)
		return (ft_malloc(size, TINY, g_lst_tiny));
	else if (size <= SMALL_SIZE_MAX)
		return (ft_malloc(size, SMALL, g_lst_small));
	else
		return (ft_malloc_large(size));
}