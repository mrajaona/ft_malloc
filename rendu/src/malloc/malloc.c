#include "ft_malloc.h"

static t_identifier	*ft_malloc_large(size_t size)
{
	void	*ptr;
	t_identifier *id;

	ptr = mmap(NULL, size + sizeof(t_identifier), MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET);
	id = (t_identifier *)ptr;
	id->addr = ptr + sizeof(t_identifier);
	id->type = LARGE;
	id->size = size;
	id->prev = NULL;
	id->next = NULL;
	return (id);
}

/*
** allocate size + sizeof(t_identifier)
** sets identifier
** returns id.addr
*/
void	*malloc(size_t size)
{
	t_identifier *id;

	id = NULL;
	if (size > SMALL_MAX)
		id = ft_malloc_large(size);
	return (id->addr);
}