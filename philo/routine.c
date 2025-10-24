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

void	take_forks(t_philo *p, pthread_mutex_t *forks[])
{
	long	start_time;

	start_time = p->config->start_time;
	if (p->config->total_philo == 1)
	{
		pthread_mutex_lock(&p->fork);
		timestamp(p->id, TAKE_FORK, start_time);
		ft_sleep_ms(p->config->tt_die);
		// philosopher dies because he can't take the second fork
		pthread_mutex_unlock(&p->fork);
		return ;
	}
	else if (p->id % 2 == 0)
	{
		// Even id: start taking LEFT fork
		pthread_mutex_lock(forks[L]);
		timestamp(p->id, TAKE_FORK, start_time);
		pthread_mutex_lock(forks[R]);
		timestamp(p->id, TAKE_FORK, start_time);
	}
	else
	{
		// Odd id: start taking RIGHT fork
		pthread_mutex_lock(forks[R]);
		timestamp(p->id, TAKE_FORK, start_time);
		pthread_mutex_lock(forks[L]);
		timestamp(p->id, TAKE_FORK, start_time);
	}
}

pthread_mutex_t *right_fork(t_philo *p)
{
	if (p->id == p->config->total_philo - 1)
		return (&p->config->philo_arr[0].fork);
	else
		return (&p->config->philo_arr[p->id + 1].fork);
}

void	eat(t_philo *p)
{
	pthread_mutex_t	*forks[2];

	// SET FORKS:
	forks[L] = &p->fork;
	forks[R] = right_fork(p);

	// TAKE FORKS:
	take_forks(p, forks);
	timestamp(p->id, EAT, p->config->start_time);
	ft_sleep_ms(p->config->tt_eat);
	// PUT DOWN FORKS:
	pthread_mutex_unlock(forks[L]);
	pthread_mutex_unlock(forks[R]);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!p->config->start_time)
		ft_sleep_ms(1);
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
