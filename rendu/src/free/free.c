#include "free.h"

void	free(void *ptr)
{
	if (pthread_mutex_lock(&g_mutex) != 0)
		return ;
	write(1, "\nf", 2); // debug
	pthread_mutex_unlock(&g_mutex);
}