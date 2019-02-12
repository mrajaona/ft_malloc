#include "ft_malloc.h"

size_t			align(size_t size)
{
	int			page_size;
	size_t		full;
	
	page_size = getpagesize();
	full = size + sizeof(t_identifier);
	while (full % page_size)
		full++;
	return (full);
}