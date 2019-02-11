#include "ft_malloc.h"

void	free(void *ptr)
{
	t_identifier	*id;

	write(1, "free\n", 5);
	if (ptr == NULL)
		return ;
	id = (t_identifier *)(ptr - sizeof(t_identifier));
	if (id->type == LARGE)
		munmap(id, id->size + sizeof(t_identifier));
}