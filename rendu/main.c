#include <unistd.h>
#include <pthread.h>

#include "ft_malloc.h"
/*
pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
    void *a = NULL;
	void *b = NULL;
	void *c = NULL;

	a = malloc(1 << 6);
	b = malloc(0);
	c = malloc(1 << 11);

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	show_mem_alloc();
	write(1, "1 --\n", 5);

	free(a); a = NULL;
	free(b); b = NULL;
	free(c); c = NULL;

	show_mem_alloc();
	write(1, "2 --\n", 5);
	(void)arg;
    return NULL;
}
*/
int main(void)
{
/*
    int i = 0;

    if (pthread_mutex_init(&lock, NULL) != 0)
        return 1;

    while(i < 2)
    {
        pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
*/
//    doSomeThing(NULL);
    show_mem_alloc();
    return 0;
}