/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:43 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:43 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "identify.h"

static t_elem_info	*find_in_zone(t_elem_info *first, const void *ptr)
{
	t_elem_info	*elem;

	elem = first;
	while (elem)
	{
		if ((void *)elem + sizeof(t_elem_info) == ptr)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

static t_elem_info	*check_zone(t_zone_info *zone, const void *ptr)
{
	if (ptr < (void *)(zone->first)
		|| ptr > ((void *)(zone->first) + zone->size))
		return (NULL);
	return (find_in_zone(zone->first, ptr));
}

t_elem_info			*identify(const void *ptr)
{
	t_zone_info	*zone;
	t_elem_info	*elem;

	if (!ptr)
		return (NULL);
	zone = g_zones.tiny;
	while (zone)
	{
		if (NULL != (elem = check_zone(zone, ptr)))
			return (elem);
		zone = zone->next;
	}
	zone = g_zones.small;
	while (zone)
	{
		if (NULL != (elem = check_zone(zone, ptr)))
			return (elem);
		zone = zone->next;
	}
	return (find_in_zone(g_zones.large, ptr));
}
