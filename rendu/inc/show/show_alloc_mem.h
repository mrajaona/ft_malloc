/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:28:27 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:28:28 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOW_ALLOC_MEM_H
# define SHOW_ALLOC_MEM_H

# include <pthread.h>
# include <unistd.h>

/*
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include "ft_printf.h"
# include "global.h"

# include "show_type.h"
# include "show_item.h"

void	show_alloc_mem(void);

#endif
