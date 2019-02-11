#include "ft_malloc.h"

size_t				align(size_t size)
{
	int				page_size;
	size_t			full;
	
	page_size = getpagesize();
	full = size + sizeof(t_identifier);
	while (full % page_size)
		full++;
	return (full);
}

static t_identifier	*ft_malloc_large(size_t size)
{
	void			*ptr;
	t_identifier	*id;
	size_t			aligned;

	aligned = align(size);
	ptr = mmap(NULL, aligned, MMAP_PROT, MMAP_FLAGS, MMAP_FD, MMAP_OFFSET);
	id = (t_identifier *)ptr;
	id->type = LARGE;
	id->size = aligned - sizeof(t_identifier);
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
	t_identifier	*id;

	write(1, "malloc\n", 7);
	id = NULL;
	// if (size > SMALL_MAX)
		id = ft_malloc_large(size);
	return (id + sizeof(t_identifier));
}