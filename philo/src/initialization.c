/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:42:37 by danielji          #+#    #+#             */
/*   Updated: 2025/08/21 10:32:13 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philosophers.h"

/* TO DO: Parse valid numbers (exclude text, negative numbers, etc) */
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
	return (config);
}

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
	t_philo	*array;

	array = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!array)
		return (NULL);
	i = 0;
	while (i < n)
	{
		array[i] = init_philo(i + 1);
		i++;
	}
	return (array);
}
