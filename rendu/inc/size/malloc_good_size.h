/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_good_size.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:00:14 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:00:15 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_GOOD_SIZE_H
# define MALLOC_GOOD_SIZE_H

# include <pthread.h>
# include <stddef.h>

# include "global.h"

size_t	malloc_good_size_thread(size_t size);
size_t	malloc_good_size(size_t size);

#endif
