/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_check_size.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:00:07 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:00:08 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_CHECK_SIZE_H
# define MALLOC_CHECK_SIZE_H

# include <pthread.h>
# include <stddef.h>

# include <sys/resource.h>
# include <sys/time.h>
# include <limits.h>

# include "global.h"
# include "malloc_good_size.h"

size_t	malloc_check_size(size_t size);

#endif
