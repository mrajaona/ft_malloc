#include "ft_malloc_util.h"

t_zone_id	*create_zone(enum e_type type)
{
	(void)type;
	// create zone
	;
	// create single free chunk
	;
	// add to lst
	;
	return (NULL);
}

t_chunk_id	*check_zone(t_zone_id *zone, size_t size)
{
	t_chunk_id	*id;

	id = (t_chunk_id *)(zone + sizeof(t_zone_id));
	size = chunk_align(size);
	while (id)
	{
		if (id->isfree == true && id->size >= size)
			return (id);
		id = id->next;
	}
	return (NULL);
}