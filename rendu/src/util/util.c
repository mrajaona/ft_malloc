#include "ft_malloc_util.h"

t_chunk_id	*identify(void *addr)
{
	t_chunk_id	*id;

	if (!addr)
		return (NULL);

	id = (t_chunk_id *)((char *)addr - sizeof(t_chunk_id));
	
	if (id)
		write(1, "1", 1);
	if (id->addr)
		write(1, "2", 1);

	// check valid id
	if (id->addr != addr)
	{
		write(1, "\nbug identify\n", 14);
		return (NULL);
	}

	return (id);
}
