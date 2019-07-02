#include "split.h"

/*
** sets first elem as allocated
** and second elem as free
*/

void	split(t_elem_info *first, const size_t size)
{
	t_elem_info	*second;
	size_t		second_size;

	if (!first)
		return ;
	first->isfree = 0;
	if (first->size < size) // Error : Not enough space
		return ;
	if (first->size == size)
		return ;
	second_size = first->size - (size + sizeof(t_zone_info));
	if (second_size < sizeof(t_zone_info))
		return ; // Not enough space to split

	second = (void *)first + sizeof(t_zone_info) + size;
	second->isfree = 1;
	second->size = second_size;
	second->addr = (void *)second + sizeof(t_elem_info);
	second->prev = first;
	second->next = first->next;
	first->next = second;
	first->size = size;

	while (second->next && second->next->isfree)
		merge(second, second->next);
}
