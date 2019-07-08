/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_other.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:27:56 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:27:57 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_OTHER_H
# define MALLOC_OTHER_H

# include <sys/mman.h>

/*
** void *mmap(void *addr, size_t length, int prot, int flags, int fd,
** off_t offset);
*/

# include <unistd.h>

/*
** int getpagesize(void);
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include <errno.h>

# include "memory.h"
# include "global.h"

# include "split.h"

void	*other(size_t size, const t_type type);

#endif
