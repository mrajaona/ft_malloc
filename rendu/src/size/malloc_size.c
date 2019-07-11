/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:01:31 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:01:31 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_size.h"

size_t	malloc_size_thread(const void *ptr)
{
	t_elem_info	*elem;

	if ((elem = identify(ptr)) != NULL)
		return (elem->size);
	return (0);
}

size_t	malloc_size(const void *ptr)
{
	size_t	ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (0);
	ret = malloc_size_thread(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
