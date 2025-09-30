#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct s_th
{
	pthread_t	id;
	pthread_mutex_t *m;
	int prueba;
} t_th;

void *function(void *arg)
{
	t_th *hilo;
	hilo = (t_th *)arg;
	printf("%d p\n", hilo->prueba);
	usleep(2000000);
	printf("Created a new thread \n");
	pthread_mutex_unlock(hilo->m);
	return (NULL);
}



int	main()
{
	t_th hilo;
	
	pthread_t	id;
	pthread_mutex_t *m;
	m = malloc(sizeof(pthread_mutex_t));
	hilo.m = m;
	hilo.prueba = 0;
	pthread_create(&id, NULL, function, &hilo);
	printf("%d \n", m->__data.__lock);
	pthread_mutex_lock(m);
	printf("%d \n", m->__data.__lock);
	pthread_mutex_lock(m);
	printf("%d \n", m->__data.__lock);
	pthread_mutex_unlock(m);
	pthread_mutex_lock(m);
	printf("%d \n", m->__data.__lock);
	pthread_mutex_unlock(m);
	pthread_join(id, NULL);
}