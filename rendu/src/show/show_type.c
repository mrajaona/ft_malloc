/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:54:09 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:54:09 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show_type.h"

void	show_tiny(t_zone_info *zone, unsigned long long *total)
{
	ft_printf("%s : %p\n", "TINY", zone);
	show_zone(zone, total);
}

void	show_small(t_zone_info *zone, unsigned long long *total)
{
	ft_printf("%s : %p\n", "SMALL", zone);
	show_zone(zone, total);
}

void	show_large(t_elem_info *elem, unsigned long long *total)
{
	ft_printf("%s : %p\n", "LARGE", elem);
	show_elem(elem, total);
}
