#ifndef GLOBAL_H
# define GLOBAL_H

# include "memory.h"

typedef struct	s_zones
{
	t_zone_info	*tiny;
	t_zone_info	*small;
	t_zone_info	*large;
}				t_zones;

extern t_zones	g_zones;

#endif