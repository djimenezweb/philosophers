/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:10:34 by danielji          #+#    #+#             */
/*   Updated: 2025/10/25 13:10:39 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_any_philo_dead(t_config *config)
{
	int i;

	i = 0;
	while (i < config->total_philo)
	{
		pthread_mutex_lock(&config->philo_arr[i].last_lunch_mtx);
		if (getmilliseconds() - config->philo_arr[i].last_lunch >= config->tt_die)
		{
			config->philo_arr[i].is_dead = 1;
			timestamp(config->philo_arr[i].id, DIE, config->start_time);
			set_stop(config, 1);
			pthread_mutex_unlock(&config->philo_arr[i].last_lunch_mtx);
			return (1);
		}
		pthread_mutex_unlock(&config->philo_arr[i].last_lunch_mtx);
		i++;
	}
	return (0);
}

void	*obs_routine(void *arg)
{
	t_config	*config;

	config = (t_config *)arg;
	while (1)
	{
		if (is_any_philo_dead(config) == 1)
			break ;
	}
	return (NULL);
}