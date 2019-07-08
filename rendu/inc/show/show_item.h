/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_item.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:28:27 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:28:28 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOW_ITEM_H
# define SHOW_ITEM_H

# include "memory.h"
# include "ft_printf.h"

void	show_elem(t_elem_info *elem, unsigned long long *total);
void	show_zone(t_zone_info *zone, unsigned long long *total);

#endif
