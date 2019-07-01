#include "ft_malloc_util.h"

// debug
/*
#include "ft_malloc_print.h"
static void	ft_debug(const t_chunk_id *chunk)
{
	char	buf[BUFSIZE];

	ft_clrbuf(buf);
	ft_put_addr(chunk, buf);
	ft_append(buf, SEP_ADDR);
	ft_put_addr((char *)chunk + sizeof(t_chunk_id), buf);
	ft_print_ln(buf, STDOUT);
}
*/
static void	ft_free_zone(const enum e_type type, t_zone_id *zone)
{
	if (zone->next)
		zone->next->prev = zone->prev;
	if (zone->prev)
		zone->prev->next = zone->next;
	else
	{
		if (type == TINY)
			g_lst.tiny = zone->next;
		else
			g_lst.small = zone->next;
	}
	munmap(zone, zone->size);	
}

static void	ft_free_large(t_chunk_id *id)
{
	if (id->next)
		id->next->prev = id->prev;
	if (id->prev)
		id->prev->next = id->next;
	else
		g_lst.large = id->next;

	munmap(id, id->size); // bug
}

void	ft_free(void *addr)
{
	t_chunk_id	*id;

	if (!addr)
	{
		write(1, "no addr to free\n", 16);
		return ;
	}
	if ((id = identify(addr)) == NULL) // invalid addr
	{
		write(1, "invalid free\n", 13);
		return ;
	}
	// ft_debug(id);
	if (id->type != LARGE)
	{
		id->isfree = true;
		if (id->next && id->next->isfree == true)
			merge(id, id->next);
		if (id->prev && id->prev->isfree == true)
		{
			id = id->prev;
			merge(id, id->next);
		}
		if (!(id->prev) && !(id->next)) // empty zone
			ft_free_zone(id->type,
				(t_zone_id *)((char *)id - sizeof(t_zone_id)));
	}
	else // if (id->type == LARGE)
		ft_free_large(id);
}