#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "ft_malloc.h"

#define SIZE_T 100
#define SIZE_S 500
#define SIZE_L 1050

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
	void *a = NULL;
	void *b = NULL;
	void *c = NULL;

	(void)arg;

	a = malloc(1 << 6);
	b = malloc(0);
	c = malloc(1 << 11);

	if (!a) write(1, "!a\n", 3);
	if (!b) write(1, "!b\n", 3);
	if (!c) write(1, "!c\n", 3);

	show_alloc_mem();
	write(1, "1 --\n", 5);

	free(a); a = NULL;
	free(b); b = NULL;
	free(c); c = NULL;

	show_alloc_mem();
	write(1, "2 --\n", 5);
	return NULL;
}

int main(void)
{
	write(1, "thread\n", 7);
	getchar();

	{
		int i = 0;

		if (pthread_mutex_init(&lock, NULL) != 0)
			return 1;

		while (i < 2)
		{
			pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
			i++;
		}

		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
		pthread_mutex_destroy(&lock);
	}

	write(1, "thread\n", 7);
	getchar();
	{
		size_t	tab[] = {SIZE_T, SIZE_S, SIZE_L};
		char	*tmp[10];
		int		i;


		write(1, "malloc\n", 7);
		getchar();
		i = 0;
		while (i < 10)
		{
			tmp[i] = malloc(tab[i % 3]);
			if (tmp[i])
			{
				strcpy(tmp[i], "test\n");
				write(1, tmp[i], 5);
			}
			else
				write(1, "not allocated\n", 14);
			i++;
		}

		getchar();
		show_alloc_mem();
		write(1, "\n", 1);

		
		write(1, "realloc\n", 8);
		getchar();
		i = 0;
		while (i < 10)
		{
			tmp[i] = realloc(tmp[i], 1);
			i++;
		}

		getchar();
		show_alloc_mem();
		write(1, "\n", 1);

		write(1, "realloc (free)\n", 15);
		getchar();
		i = 0;
		while (i < 10)
		{
			tmp[i] = realloc(tmp[i], 20);
			i++;
		}

		getchar();
		show_alloc_mem();
		write(1, "\n", 1);

		write(1, "realloc (malloc)\n", 17);
		getchar();
		i = 0;
		while (i < 10)
		{
			tmp[i] = realloc(tmp[i], SIZE_S);
			i++;
		}

		getchar();
		show_alloc_mem();
		write(1, "\n", 1);

		write(1, "free\n", 5);
		getchar();
		i = 0;
		while (i < 10)
		{
			free(tmp[i]);
			i++;
		}

		getchar();
		show_alloc_mem();
		write(1, "\n", 1);
	}

	write(1, "\n", 1);

	{
		char	*tmp;

		write(1, "malloc\n", 7);
		getchar();
		tmp = malloc(1);
		
		getchar();
		show_alloc_mem();
		write(1, "\n", 1);
		
		if (tmp)
		{
			*tmp = 'a';
			write(1, tmp, 1);
			write(1, "\n", 1);
		}

		write(1, "free\n", 5);
		getchar();
		free(tmp);
		
		getchar();
		show_alloc_mem();
		write(1, "\n", 1);
	}

	while (1) {}

	return (0);
}