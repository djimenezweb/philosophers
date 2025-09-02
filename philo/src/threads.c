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

void	put_down_forks(t_philo p)
{
	pthread_mutex_unlock(p.left_fork);
	timestamp(p.id, DOWN_FORK);
	pthread_mutex_unlock(p.right_fork);
	timestamp(p.id, DOWN_FORK);
}

void	take_forks(t_philo p)
{
	pthread_mutex_lock(p.left_fork);
	timestamp(p.id, TAKE_FORK);
	pthread_mutex_lock(p.right_fork);
	timestamp(p.id, TAKE_FORK);
}

void	eat(t_philo p)
{
	take_forks(p);
	timestamp(p.id, EAT);
	ft_sleep_ms(p.config.tt_eat);
	put_down_forks(p);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
/* 	if (p->id % 2 == 0)
		ft_sleep_ms(1); */
	eat(*p);
	timestamp(p->id, SLEEP);
	ft_sleep_ms(p->config.tt_sleep);
	timestamp(p->id, THINK);
	return (NULL);
}

/* Creates and join one thread per philosopher */
void	create_threads(t_config config)
{
	int		i;
	t_philo	p;

	i = 0;
	while (i < config.total_philo)
	{
		p = config.philo_array[i];
		pthread_create(&p.thread, NULL, routine, (void *)&p);
		pthread_join(p.thread, NULL);
		i++;
	}
}
