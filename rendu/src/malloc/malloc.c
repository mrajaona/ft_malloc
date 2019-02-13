#include "ft_malloc_util.h"

t_zone_id	*g_lst_tiny = NULL;
t_zone_id	*g_lst_small = NULL;
t_chunk_id	*g_lst_large = NULL;


static void	*ft_malloc(size_t size, enum e_type type, t_zone_id **lst)
{
	t_chunk_id	*id;
	t_zone_id	*cursor;

	if (!lst) // ???
		return (NULL);
	cursor = *lst; // can be NULL
	id = NULL;
	while (cursor && !id)
	{
		id = check_zone(cursor, size);
		cursor = cursor->next;
	}
	if (!id) // need new zone
	{
		if ((cursor = create_zone(lst, type)) == NULL)
			return (NULL);
		id = (t_chunk_id *)(cursor + sizeof(t_zone_id));
	}
	split(id, size);
	return (id);
}

static void	*ft_malloc_large(size_t size)
{
	size_t		length;
	t_chunk_id	*id;
	
	length = mmap_align(chunk_align(size));
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
		return (ft_malloc(size, TINY, &g_lst_tiny));
	else if (size <= SMALL_SIZE_MAX)
		return (ft_malloc(size, SMALL, &g_lst_small));
	else
		return (ft_malloc_large(size));
}