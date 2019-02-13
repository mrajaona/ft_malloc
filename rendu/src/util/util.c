#include "ft_malloc_util.h"

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
