/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:57 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:58 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

/*
** sets first elem as allocated
** and second elem as free
*/

#include "ft_printf.h" // debug

void	split(t_elem_info *first, const size_t size)
{
	t_elem_info	*second;
	size_t		second_size;

	if (!first)
		return ;
	first->isfree = 0;
	if (first->size < size)
		return ;
	if (first->size == size || (first->size - size) < sizeof(t_elem_info))
		return ;
	second_size = first->size - (size + sizeof(t_elem_info));
	first->size = size;
	second = first->addr + first->size;
	second->isfree = 1;
	second->size = second_size;
	second->addr = (void *)second + sizeof(t_elem_info);
	second->prev = first;
	second->next = first->next;
	first->next = second;
	if (second->next && second->next->isfree)
		merge(second, second->next);
	if (second->next)
		second->next->prev = second;

	// debug
	ft_printf("%s\n\telem %llu (%llu)\n\taddr %llu (%llu)\n", "split first",
		(unsigned long long)first,
		(unsigned long long)first % 16,
		(unsigned long long)(first->addr),
		(unsigned long long)(first->addr) % 16
	);
	ft_printf("%s\n\telem %llu (%llu)\n\taddr %llu (%llu)\n", "split second",
		(unsigned long long)second,
		(unsigned long long)second % 16,
		(unsigned long long)(second->addr),
		(unsigned long long)(second->addr) % 16
	);
}
