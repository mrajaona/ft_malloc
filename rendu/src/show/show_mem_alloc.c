#include "ft_malloc_print.h"

static bool ft_smallest(void *a, void *b, void *c)
{
	if (!a)
		return (false);
	if ((!b || a < b) && (!c || a < c))
		return (true);
	return (false);
}

static bool	ft_check(t_list *c, size_t *total)
{
	if (c->tiny && ft_smallest(c->tiny, c->small, c->large) == true)
	{
		ft_print_header(c->tiny, TINY);
		ft_print_zone(c->tiny, total);
		c->tiny = c->tiny->next;
	}
	else if (c->small && ft_smallest(c->small, c->tiny, c->large) == true)
	{
		ft_print_header(c->small, SMALL);
		ft_print_zone(c->small, total);
		c->small = c->small->next;
	}
	else if (c->large && ft_smallest(c->large, c->tiny, c->small) == true)
	{
		ft_print_header(c->large, LARGE);
		ft_print_chunk(c->large);
		*total += c->large->size - sizeof(t_chunk_id);
		c->large = c->large->next;
	}
	else
		return (false);
	return (true);
}

void	ft_show_mem_alloc()
{
	t_list	c;
	size_t	total;

	c = g_lst;
	total = 0;
	while (c.tiny || c.small || c.large)
	{
		if (!ft_check(&c, &total))
			{
				ft_print_ln(ERR_UNKNOWN_TYPE, STDERR);
				return ;
			}
	}
	ft_print_total(total);
}