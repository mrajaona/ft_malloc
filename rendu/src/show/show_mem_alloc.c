#include "ft_malloc_util.h"
#include "ft_malloc_print.h"

static void	ft_put_size(const size_t size, char buf[BUFSIZE])
{
	ft_nbr(buf, size, 10);
	ft_append(buf, UNIT);
}

static void	ft_put_addr(const void *addr, char buf[BUFSIZE])
{
	ft_append(buf, HEAD_HEX);
	ft_nbr(buf, (size_t)addr, 16);
}

static void	ft_print_total(const size_t total) // in bytes
{
	char	buf[BUFSIZE];

	ft_clrbuf(buf);
	ft_append(buf, HEAD_TOTAL);
	ft_append(buf, SEP_DATA);
	ft_put_size(total, buf);

	ft_print_ln(buf, STDOUT);
}

static void	ft_print_chunk(const t_chunk_id *chunk)
{
	char	buf[BUFSIZE];

	ft_clrbuf(buf);
	ft_put_addr(chunk, buf); // start
	ft_append(buf, SEP_ADDR);
	ft_put_addr((char *)chunk + chunk->size - 1, buf); // end
	ft_append(buf, SEP_DATA);
	ft_put_size(chunk->size, buf); // size // bytes

	ft_print_ln(buf, STDOUT);
}

static void	ft_print_zone(const t_zone_id *zone, size_t *total)
{
	t_chunk_id	*chunk;

	chunk = (t_chunk_id *)((char *)zone + sizeof(t_zone_id));
	while (chunk)
	{
		if (chunk->isfree == false)
		{
			ft_print_chunk(chunk);
			*total += chunk->size;
		}
		chunk = chunk->next;
	}
}

static void	ft_print_header(const void *addr, const enum e_type type)
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

static bool ft_smallest(void *a, void *b, void *c)
{
	if (!a)
		return (false);
	if ((!b || a < b) && (!c || a < c))
		return (true);
	return (false);
}

void	show_mem_alloc()
{
	write(1, "\nshow_mem_alloc\n", 16);

	t_list	c;
	size_t	total;

	c = g_lst;
	total = 0;
	while (c.tiny || c.small || c.large)
	{
		if (c.tiny && ft_smallest(c.tiny, c.small, c.large) == true)
		{
			ft_print_header(c.tiny, TINY);
			ft_print_zone(c.tiny, &total);
			c.tiny = c.tiny->next;
		}
		else if (c.small && ft_smallest(c.small, c.tiny, c.large) == true)
		{
			ft_print_header(c.small, SMALL);
			ft_print_zone(c.small, &total);
			c.small = c.small->next;
		}
		else if (c.large && ft_smallest(c.large, c.tiny, c.small) == true)
		{
			ft_print_header(c.large, LARGE);
			ft_print_chunk(c.large);
			total += c.large->size;
			c.large = c.large->next;
		}
		else
			write(1, ".", 1); // debug // error
	}
	ft_print_total(total);
}