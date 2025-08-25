/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:44:37 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 11:43:37 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* void	*routine(void *arg)
{
	t_config	*c;

	c = (t_config *)arg;
	timestamp(1, "says hello");
	return (NULL);
} */

void	*routine(void *arg)
{
	t_philo			*p;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;

	p = (t_philo *)arg;
	timestamp(p->id, "says hello");	
	if (p->id == 1)
	{
		left_fork = p->config.forks[p->id];
		right_fork = p->config.forks[p->id + 1];
		if (pthread_mutex_lock(&left_fork) == 0)
			timestamp(p->id, "takes left fork");
		else
			printf("Something went wrong! (left)\n");
		if (pthread_mutex_lock(&right_fork) == 0)
			timestamp(p->id, "takes right fork");
		else
			printf("Something went wrong! (right)\n");
	}
	return (NULL);
}

void	create_threads(t_config config)
{
	int			i;
	pthread_t	thread;
	t_philo		p;

	i = 0;
	while (i < config.number)
	{
		p = config.philo_array[i];
		p.thread = thread;
		pthread_create(&thread, NULL, routine, (void *)&p);
		pthread_join(thread, NULL);
		i++;
	}
}
