/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:07:07 by danielji          #+#    #+#             */
/*   Updated: 2025/10/24 10:07:07 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *p, pthread_mutex_t *lfork, pthread_mutex_t *rfork)
{
	long	start_time;

	start_time = p->config->start_time;
	if (p->config->total_philo == 1)
	{
		// TO DO: Only 1 philosopher
	}
	else if (p->id % 2 == 0)
	{
		// Even id: start taking LEFT fork
		pthread_mutex_lock(lfork);
		timestamp(p->id, TAKE_FORK, start_time);
		pthread_mutex_lock(rfork);
		timestamp(p->id, TAKE_FORK, start_time);
	}
	else
	{
		// Odd id: start taking RIGHT fork
		pthread_mutex_lock(rfork);
		timestamp(p->id, TAKE_FORK, start_time);
		pthread_mutex_lock(lfork);
		timestamp(p->id, TAKE_FORK, start_time);
	}
}

void	eat(t_philo *p)
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;

	// SET FORKS:
	lfork = &p->fork;
	if (p->id == p->config->total_philo)
		rfork = &p->config->philo_arr[0].fork;
	else
		rfork = &p->config->philo_arr[p->id + 1].fork;
	// TAKE FORKS:
	take_forks(p, lfork, rfork);
	timestamp(p->id, EAT, p->config->start_time);
	ft_sleep_ms(p->config->tt_eat);
	// PUT DOWN FORKS:
	pthread_mutex_unlock(lfork);
	pthread_mutex_unlock(rfork);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		// Si es par se retrasa 1ms para que empiece más tarde
		// pero no me gusta esta solución
		if (p->id % 2 == 0)
			ft_sleep_ms(1);

		// EAT
		eat(p);

		// SLEEP
		timestamp(p->id, SLEEP, p->config->start_time);
		ft_sleep_ms(p->config->tt_sleep);

		// THINK
		timestamp(p->id, THINK, p->config->start_time);
	}
	return (NULL);
}
