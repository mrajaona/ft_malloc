#include "ft_malloc_util.h"

// merge consecutive slots
void	merge(t_chunk_id *first, t_chunk_id *second)
{
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	first->size = first->size + second->size;

	second->addr = NULL;
	second->size = 0;
	second->isfree = true;
	second->prev = NULL;
	second->next = NULL;
}

void	split(t_chunk_id *first, size_t size)
{
	t_chunk_id	*second;
	size_t		aligned;
	size_t		second_size;

	aligned = chunk_align(size);
	second_size = first->size - aligned; // TODO : check aligned

	first->size = aligned;
	second = first + first->size;

	second->size = second_size;

	first->isfree = false;
	second->isfree = true;

	second->prev = first;
	second->next = first->next;

	first->next = second;
}

size_t		chunk_align(size_t size)
{
	size_t	aligned;

	aligned = size + sizeof(t_chunk_id);
	return (aligned);
}

size_t		mmap_align(size_t size)
{
	int			page_size;
	
	page_size = getpagesize();
	while (size % page_size)
		size++;
	return (size);
}

t_chunk_id	*identify(void *addr)
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
