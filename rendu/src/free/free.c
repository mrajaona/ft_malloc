#include "ft_malloc_util.h"

void	free(void *addr)
{
	t_chunk_id	*id;
	t_zone_id	*zone;

	write(1, "\nf", 2);
	if (!addr)
	{
		write(1, "0", 1);
		return ;
	}
	if ((id = identify(addr)) == NULL) // invalid addr
		return ;
	if (id->type != LARGE)
	{
		write(1, "s", 1);
		id->isfree = true;
		if (id->next && id->next->isfree == true)
			merge(id, id->next);

		if (!(id->prev) && !(id->next)) // empty zone
		{
			write(1, "~", 1);
			zone = (t_zone_id *)(id - sizeof(t_zone_id));
			if (zone->next)
				zone->next->prev = zone->prev;
			if (zone->prev)
				zone->prev->next = zone->next;
			else
			{
				if (id->type == TINY)
					g_lst_tiny = zone->next;
				else
					g_lst_small = zone->next;
			}
			munmap(zone, zone->size);
			write(1, "F", 1);
		}

	}
	
	else // if (id->type == LARGE)
	{
		write(1, "L", 1);
		if (id->next)
			id->next->prev = id->prev;
		if (id->prev)
			id->prev->next = id->next;
		else
			g_lst_large = id->next;
		munmap(id, id->size);
		write(1, "F", 1);
	}

}