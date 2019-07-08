/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:28:27 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:28:28 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOW_TYPE_H
# define SHOW_TYPE_H

# include "memory.h"
# include "ft_printf.h"

# include "show_item.h"

void	show_tiny(t_zone_info *zone, unsigned long long *total);
void	show_small(t_zone_info *zone, unsigned long long *total);
void	show_large(t_elem_info *elem, unsigned long long *total);

#endif
