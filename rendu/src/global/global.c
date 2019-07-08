/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:31:54 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:31:55 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

t_zones			g_zones = {.tiny = NULL, .small = NULL, .large = NULL};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
