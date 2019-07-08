/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:27:37 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:27:38 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include <pthread.h>

# include <unistd.h>

/*
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include <sys/mman.h>

/*
** int munmap(void *addr, size_t length);
*/

# include "global.h"

# include "identify.h"
# include "merge.h"
# include "get_type.h"

void	free(void *ptr);
void	free_thread(void *ptr);

#endif
