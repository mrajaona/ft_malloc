/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:28:19 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:28:20 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REALLOC_H
# define REALLOC_H

# include <pthread.h>

# include <unistd.h>

/*
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include "malloc_check_size.h"

# include "malloc.h"
# include "free.h"
# include "ft_memcpy.h"

# include "identify.h"

# include "memory.h"
# include "global.h"

# include "get_type.h"
# include "merge.h"
# include "split.h"

void	*realloc_thread(void *ptr, size_t size);
void	*realloc(void *ptr, size_t size);

#endif
