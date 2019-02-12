#include "ft_malloc_util.h"

size_t			align(size_t size)
{
	int			page_size;
	
	page_size = getpagesize();
	while (size % page_size)
		size++;
	return (size);
}

t_chunk_id			*identify(void *addr)
{
	t_chunk_id	*id;

	if (!addr)
		return (NULL);
	id = (t_chunk_id *)(addr - sizeof(t_chunk_id));
	// check valid id
	if (id->addr != addr)
		return (NULL);
	return (id);
}

