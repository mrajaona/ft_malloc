/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:27:56 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:27:57 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>

# include <errno.h>

# include "memory.h"
# include "global.h"
# include "get_type.h"

# include "malloc_check_size.h"

# include "malloc_large.h"
# include "malloc_other.h"

void	*malloc(size_t size);
void	*malloc_thread(size_t size);

#endif
