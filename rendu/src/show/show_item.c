/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:54:02 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:54:04 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show_item.h"

void	show_elem(t_elem_info *elem, unsigned long long *total)
{
	ft_printf("%p - %p : %llu\n",
		(void *)elem + sizeof(t_elem_info),
		(void *)elem + sizeof(t_elem_info) + elem->size - 1,
		elem->size);
	*total += elem->size;
}

void	show_zone(t_zone_info *zone, unsigned long long *total)
{
	t_elem_info	*cursor;

	cursor = zone->first;
	while (cursor)
	{
		if (!(cursor->isfree))
			show_elem(cursor, total);
		cursor = cursor->next;
	}
}
