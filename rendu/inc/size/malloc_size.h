/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_size.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:00:21 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:00:21 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_SIZE_H
# define MALLOC_SIZE_H

# include <pthread.h>
# include <stddef.h>

# include "global.h"
# include "memory.h"
# include "identify.h"

size_t	malloc_size_thread(const void *ptr);
size_t	malloc_size(const void *ptr);

#endif
