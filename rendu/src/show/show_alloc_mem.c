/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:27 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:27 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show_alloc_mem.h"

static void	*get_first(void *a, void *b, void *c)
{
	void	*first;

	first = a;
	if (!first || (b && b < first))
		first = b;
	if (!first || (c && c < first))
		first = c;
	return (first);
}

static void	show(t_zones *zones, void *first, unsigned long long *total)
{
	if (first == (void *)(zones->tiny))
	{
		show_tiny(zones->tiny, total);
		zones->tiny = zones->tiny->next;
	}
	else if (first == (void *)(zones->small))
	{
		show_small(zones->small, total);
		zones->small = zones->small->next;
	}
	else if (first == (void *)(zones->large))
	{
		show_large(zones->large, total);
		zones->large = zones->large->next;
	}
	else
		write(2, "Error : unknown allocation.\n", 28);
}

static void	show_alloc_mem_thread(void)
{
	t_zones				zones;
	void				*first;
	unsigned long long	total;

	zones = g_zones;
	total = 0;
	while (zones.tiny || zones.small || zones.large)
	{
		if (!(first = get_first(zones.tiny, zones.small, zones.large)))
			break ;
		show(&zones, first, &total);
	}
	ft_printf("Total : %llu\n", total);
}

void		show_alloc_mem(void)
{
	if (pthread_mutex_lock(&g_mutex) != 0)
		return ;
	show_alloc_mem_thread();
	pthread_mutex_unlock(&g_mutex);
}
