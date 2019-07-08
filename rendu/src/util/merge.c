/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:50 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:51 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"

t_elem_info	*merge(t_elem_info *lhs, t_elem_info *rhs)
{
	if (!lhs || !rhs)
		return (lhs);
	lhs->size = lhs->size + sizeof(t_elem_info) + rhs->size;
	if (rhs->next)
		rhs->next->prev = lhs;
	lhs->next = rhs->next;
	return (lhs);
}
