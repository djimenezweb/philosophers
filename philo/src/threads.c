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

void	eat(t_philo p)
{
	int	left_fork;
	int	right_fork;

	left_fork = p.id - 1;
	if (p.id == p.config.number - 1)
		right_fork = 0;
	else
		right_fork = p.id;
	pthread_mutex_lock(&(p.config.forks[left_fork]));
	timestamp(p.id, "takes left fork");
	pthread_mutex_lock(&(p.config.forks[right_fork]));
	timestamp(p.id, "takes right fork");
	usleep(p.config.tt_eat * 1000);
	
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	timestamp(p->id, "says hello");
	eat(*p);
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
