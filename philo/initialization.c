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

/* Allocate memory and return an array of forks
(initialized `pthread_mutex_t`) */
/* pthread_mutex_t	*init_forks(int n)
{
	int				i;
	pthread_mutex_t	*arr;

	arr = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&arr[i], NULL);
		i++;
	}
	return (arr);
} */

/* - Assign `id` and reference to `config` to philosopher
- Initalize fork mutex
- Return philosopher */
t_philo	init_philo(t_config *config, int id)
{
	t_philo	p;

	p.id = id;
	p.config = config;
	pthread_mutex_init(&p.fork, NULL);
	return (p);
}

/* Allocate memory and return an array of initialized philosophers */
t_philo	*init_philo_array(t_config *config, int n)
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

/* - Return an initialized `t_config` structure
- Initialize array of philosophers
- Set start time */
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
	config->philo_arr = init_philo_array(config, config->total_philo);
	if (!config->philo_arr)
		return (-1);
	config->start_time = getmilliseconds();
	return (0);
}
