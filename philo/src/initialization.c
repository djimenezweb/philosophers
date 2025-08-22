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

/* Returns a philosopher */
t_philo	init_philo(int id)
{
	t_philo	p;

	p.id = id;
	return (p);
}

/* Returns an array of philosophers */
t_philo	*init_array(int n)
{
	int		i;
	t_philo	*arr;

	arr = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = init_philo(i + 1);
		i++;
	}
	return (arr);
}

/* Returns an initialized `t_config` structure */
t_config	init_config(int argc, char *argv[])
{
	t_config	config;

	config.number = ft_atoi(argv[1]);
	config.tt_die = ft_atoi(argv[2]);
	config.tt_eat = ft_atoi(argv[3]);
	config.tt_sleep = ft_atoi(argv[4]);
	if (argc >= 6)
		config.max_loops = ft_atoi(argv[5]);
	else
		config.max_loops = -1;
	config.philo_array = init_array(config.number);
	return (config);
}
