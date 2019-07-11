/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:03 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:04 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc_thread(size_t size)
{
	t_type	type;

	size = malloc_check_size(size);
	if (size == 0)
		return (NULL);
	type = get_type(size);
	if (type == LARGE)
		return (large(size));
	else
		return (other(size, type));
	return (NULL);
}

#include "ft_printf.h"
#include "malloc_size.h"

void	*malloc(size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	// ft_printf("%-10s : %llu\n", "malloc", size);
	ret = malloc_thread(size);
	// ft_printf("%-10s : %llu %p\n", ">>", malloc_size_thread(ret), ret);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
