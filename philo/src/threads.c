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
	timestamp(p.id, DOWN_FORK, p.config->start_time);
	pthread_mutex_unlock(p.right_fork);
	timestamp(p.id, DOWN_FORK, p.config->start_time);
}

void	take_forks(t_philo p)
{
	pthread_mutex_lock(p.left_fork);
	timestamp(p.id, TAKE_FORK, p.config->start_time);
	pthread_mutex_lock(p.right_fork);
	timestamp(p.id, TAKE_FORK, p.config->start_time);
}

void	eat(t_philo p)
{
	take_forks(p);
	timestamp(p.id, EAT, p.config->start_time);
	ft_sleep_ms(p.config->tt_eat);
	put_down_forks(p);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		ft_sleep_ms(1);
	eat(*p);
	timestamp(p->id, SLEEP, p->config->start_time);
	ft_sleep_ms(p->config->tt_sleep);
	timestamp(p->id, THINK, p->config->start_time);
	return (NULL);
}

/* Creates and join one thread per philosopher.
Returns `0` on success, returns an error number on error  */
int	create_threads(t_config *config)
{
	int	i;
	int	status;

	i = 0;
	while (i < config->total_philo)
	{
		status = pthread_create(
			&config->philo_array[i].thread,
			NULL,
			routine,
			(void *)&config->philo_array[i]
			);
		if (status != 0)
		{
			// TO DO: free something?
			return (status);
		}
		i++;
	}
	i = 0;
	while (i < config->total_philo)
	{
		status = pthread_join(config->philo_array[i].thread, NULL);
		if (status != 0)
		{
			// TO DO: free something?
			return (status);
		}
		i++;
	}
	return (0);
}
