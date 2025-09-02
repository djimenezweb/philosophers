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

/* Assigns `id` to philosopher
Assigns left and right fork
Returns a philosopher */
t_philo	init_philo(t_config config, int id)
{
	t_philo	p;

	p.id = id;
	p.config = config;
	p.left_fork = &config.forks[id - 1];
	if (id == p.config.total_philo - 1)
		p.right_fork = &config.forks[0];
	else
		p.right_fork = &config.forks[id];
	return (p);
}

/* Returns an array of forks (pthread_mutex_t) */
pthread_mutex_t	*init_forks(int n)
{
	pthread_mutex_t	*arr;

	arr = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!arr)
		return (NULL);
	return (arr);
}

/* Returns an array of philosophers */
t_philo	*init_array(t_config config, int n)
{
	int		i;
	t_philo	*arr;

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

/* Returns an initialized `t_config` structure */
t_config	init_config(int argc, char *argv[])
{
	t_config	config;

	config.total_philo = ft_atoi(argv[1]);
	config.tt_die = ft_atoi(argv[2]);
	config.tt_eat = ft_atoi(argv[3]);
	config.tt_sleep = ft_atoi(argv[4]);
	if (argc >= 6)
		config.max_loops = ft_atoi(argv[5]);
	else
		config.max_loops = -1;
	config.forks = init_forks(config.total_philo);
	config.philo_array = init_array(config, config.total_philo);
	return (config);
}
