/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_good_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:01:25 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:01:26 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_good_size.h"

size_t	malloc_good_size_thread(size_t size)
{
	return (size + size % 2);
}

size_t	malloc_good_size(size_t size)
{
	size_t	ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (0);
	ret = malloc_good_size_thread(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
