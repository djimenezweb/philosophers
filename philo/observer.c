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

/* Iterate through array of philosophers and check if anyone is dead
- Lock `last_lunch_mtx` to protect read
- If any philo is dead, set `stop_val` to `1` and return `1`
- Return `0` if every philosopher is alive */
int	is_any_philo_dead(t_config *config)
{
	int		i;
	long	delta;

	i = 0;
	while (i < config->total_philo)
	{
		pthread_mutex_lock(&config->philo_arr[i].last_lunch_mtx);
		delta = getmilliseconds() - config->philo_arr[i].last_lunch;
		pthread_mutex_unlock(&config->philo_arr[i].last_lunch_mtx);
		if (delta >= config->tt_die)
		{
			set_is_dead(&config->philo_arr[i], 1);
			ft_sleep_ms(2);
			printf(" === Philo %d is dead ===\n", config->philo_arr[i].id);
			ft_sleep_ms(2);
		}
		if (get_is_dead(&config->philo_arr[i]) == 1)
		{
			safe_print(config, config->philo_arr[i].id, DIE);
			set_stop(config, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

/* - Wait until `start_time` is set
- Run until `is_any_philo_dead` returns `1` */
void	*obs_routine(void *arg)
{
	t_config	*config;

	config = (t_config *)arg;
	while (!config->start_time)
		ft_sleep_ms(1);
	while (1)
	{
		if (is_any_philo_dead(config) == 1)
			break ;
	}
	return (NULL);
}
