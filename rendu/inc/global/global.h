/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:27:48 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:27:48 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <pthread.h>
# include "memory.h"

typedef struct			s_zones
{
	t_zone_info	*tiny;
	t_zone_info	*small;
	t_elem_info	*large;
}						t_zones;

extern t_zones			g_zones;
extern pthread_mutex_t	g_mutex;

#endif
