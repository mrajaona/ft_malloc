/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 09:59:56 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 09:59:57 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REALLOCF_H
# define REALLOCF_H

# include <pthread.h>

# include "global.h"

# include "realloc.h"
# include "free.h"

void	*reallocf_thread(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);

#endif
