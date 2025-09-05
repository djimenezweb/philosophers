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

int	put_down_forks(t_philo p)
{
	int	status;

	status = pthread_mutex_unlock(p.left_fork);
	if (status != 0)
		return (status);
	timestamp(p.id, DOWN_FORK, p.config->start_time);
	status = pthread_mutex_unlock(p.right_fork);
	if (status != 0)
		return (status);
	timestamp(p.id, DOWN_FORK, p.config->start_time);
	return (status);
}

int	take_forks(t_philo p)
{
	int	status;

	status = pthread_mutex_lock(p.left_fork);
	if (status != 0)
		return (status);
	timestamp(p.id, TAKE_FORK, p.config->start_time);
	status = pthread_mutex_lock(p.right_fork);
	if (status != 0)
		return (status);
	timestamp(p.id, TAKE_FORK, p.config->start_time);
	return (status);
}

int	eat(t_philo p)
{
	int	status;

	status = take_forks(p);
	if (status != 0)
		return (status);
	timestamp(p.id, EAT, p.config->start_time);
	ft_sleep_ms(p.config->tt_eat);
	status = put_down_forks(p);
	return (status);
}

/* ¿Cómo devolver status (un entero) si esta función debe devolver un puntero? */
void	*routine(void *arg)
{
	t_philo	*p;
	int		status;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		ft_sleep_ms(1);
	status = eat(*p);
	if (status != 0)
	{
		// TO DO
		//return (status);
	}
	timestamp(p->id, SLEEP, p->config->start_time);
	ft_sleep_ms(p->config->tt_sleep);
	timestamp(p->id, THINK, p->config->start_time);
	//return (&status);
	return (NULL);
}

int	join_threads(t_config *config, int max_threads)
{
	int	i;
	int	status;

	i = 0;
	while (i < max_threads)
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

/* - Creates one thread per philosopher
- Calls `join_threads` to wait for each thread to terminate
- Returns `0` on success, or an error number on error  */
int	create_threads(t_config *config)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < config->total_philo)
	{
		status = pthread_create(&config->philo_array[i].thread, NULL,
				routine, (void *)&config->philo_array[i]);
		if (status != 0)
		{
			// join previously created threads
			join_threads(config, i);
			// TO DO: free something?
			return (status);
		}
		i++;
	}
	status = join_threads(config, config->total_philo);
	return (status);
}
