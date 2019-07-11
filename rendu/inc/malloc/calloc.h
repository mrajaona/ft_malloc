/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 09:59:45 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 09:59:45 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLOC_H
# define CALLOC_H

# include <pthread.h>

# include "global.h"

# include "malloc.h"
# include "malloc_check_size.h"
# include "malloc_size.h"

void *calloc_thread(size_t count, size_t size);
void *calloc(size_t count, size_t size);

#endif
