#include "ft_malloc_util.h"

// merge consecutive slots
void	merge(t_chunk_id *first, t_chunk_id *second)
{
	if (!second)
		return ;
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	first->size = first->size + second->size;
}

/*
** allocate first part of a free chunk
** if split is possible
** allocate full chunk otherwise
*/
void	split(t_chunk_id *first, size_t size)
{

	t_chunk_id	*second;
	size_t		aligned;
	size_t		second_size;

	if (!first)
		return ;
	first->isfree = false;

	aligned = chunk_align(size);
	if (first->size < aligned) // Error
		return ;
	if (first->size == aligned)
		return ;

	second_size = first->size - aligned;

	if (second_size < chunk_align(0))
		return ;

	second = (t_chunk_id *)((char *)first + aligned);
	second->type = first->type;
	second->addr = (char *)second + sizeof(t_chunk_id);
	second->size = second_size;
	second->isfree = true;

	second->prev = first;
	second->next = first->next;

	first->size = aligned;
	first->next = second;
}