/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:42:37 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 10:46:37 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* - Assign `id` and reference to `config` to each philosopher
- Set `last_lunch` to an absurdly high time
- Initalize fork mutex
- Initialize `last_lunch_mtx` mutex
- Return philosopher */
t_philo	init_philo(t_config *config, int id)
{
	t_philo	p;

	p.id = id;
	p.config = config;
	p.is_dead = 0;
	p.last_lunch = 1800000000000;
	pthread_mutex_init(&p.fork, NULL);
	pthread_mutex_init(&p.last_lunch_mtx, NULL);
	return (p);
}

/* Allocate memory and return an array of initialized philosophers */
t_philo	*init_philo_array(t_config *config)
{
	int		i;
	int		n;
	t_philo	*arr;

	n = config->total_philo;
	arr = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = init_philo(config, i + 1);
		i++;
	}
	return (arr);
}

/* - Initialize `t_config` structure
- Initialize array of philosophers 
- Initialize `stop_mtx` and `safe_print_mtx` mutexes
- Return `0` on success, `-1` on error*/
int	init_config(t_config *config, int argc, char *argv[])
{
	config->total_philo = ft_atoi(argv[1]);
	config->tt_die = ft_atoi(argv[2]);
	config->tt_eat = ft_atoi(argv[3]);
	config->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->max_loops = ft_atoi(argv[5]);
	else
		config->max_loops = -1;
	config->philo_arr = init_philo_array(config);
	if (!config->philo_arr)
		return (-1);
	config->start_time = 0;
	config->stop_val = 0;
	pthread_mutex_init(&config->stop_mtx, NULL);
	pthread_mutex_init(&config->safe_print_mtx, NULL);
	return (0);
}
