#include "ft_malloc_print.h"

/*
** prints total size in bytes
*/
void	ft_print_total(const size_t total) // in bytes
{
	char	buf[BUFSIZE];

	ft_clrbuf(buf);
	ft_append(buf, HEAD_TOTAL);
	ft_append(buf, SEP_DATA);
	ft_put_size(total, buf);
	ft_print_ln(buf, STDOUT);
}

/*
** prints the available memory
** 0xADDR - 0xADDR : size
** available size printed in bytes
*/
void	ft_print_chunk(const t_chunk_id *chunk)
{
	char	buf[BUFSIZE];

	ft_clrbuf(buf);
	ft_put_addr((char *)chunk + sizeof(t_chunk_id), buf); // start
	ft_append(buf, SEP_ADDR);
	ft_put_addr((char *)chunk + chunk->size - 1, buf); // end
	ft_append(buf, SEP_DATA);
	ft_put_size(chunk->size/* - sizeof(t_chunk_id)*/, buf); // size // bytes
	ft_print_ln(buf, STDOUT);
}

/*
** prints every allocated chunk in the zone
*/
void	ft_print_zone(const t_zone_id *zone, size_t *total)
{
	t_chunk_id	*chunk;

	chunk = (t_chunk_id *)((char *)zone + sizeof(t_zone_id));
	while (chunk)
	{
		if (chunk->isfree == false)
		{
			ft_print_chunk(chunk);
			*total += chunk->size - sizeof(t_chunk_id);
		}
		chunk = chunk->next;
	}
}

/*
** prints the address of the zone
*/
void	ft_print_header(const void *addr, const enum e_type type)
{
	char	buf[BUFSIZE];
	char	*head;

	ft_clrbuf(buf);
	if (type == TINY)
		head = HEAD_TINY;
	else if (type == SMALL)
		head = HEAD_SMALL;
	else
		head = HEAD_LARGE;
	ft_append(buf, head);
	ft_append(buf, SEP_DATA);
	ft_put_addr(addr, buf);
	ft_print_ln(buf, STDOUT);
}