/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_check_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:01:16 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:01:17 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_check_size.h"

#include "ft_printf.h"

size_t	malloc_check_size(size_t size)
{
	size_t			max_size;
	struct rlimit	limit;

	if (size >= SSIZE_MAX)
		return (0);
	size = malloc_good_size_thread(size);
	getrlimit(RLIMIT_AS, &limit);
	max_size = limit.rlim_cur - sizeof(t_elem_info);
	if (max_size < size)
		return (0);
	return (size);
}
