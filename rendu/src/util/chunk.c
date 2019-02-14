#include "ft_malloc_util.h"

// merge consecutive slots
void	merge(t_chunk_id *first, t_chunk_id *second)
{
	write(1, "\nmerge ", 7);
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
//	t_chunk_id	*second;
	size_t		aligned;
	size_t		second_size;

	write(1, "\nsplit\n", 7);

	first->isfree = false;

	aligned = chunk_align(size);
	second_size = first->size - aligned;
	if (second_size < chunk_align(0))
		return ;

/*
	first->size = aligned;

	second = (t_chunk_id *)((char *)first + first->size);
	second->type = first->type;
	second->addr = (char *)second + sizeof(t_chunk_id);
	second->size = second_size;
	second->isfree = true;

	second->prev = first;
	second->next = first->next;

	first->next = second;
*/
}