#include "global.h"

t_zones			g_zones = {.tiny = NULL, .small = NULL, .large = NULL};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
