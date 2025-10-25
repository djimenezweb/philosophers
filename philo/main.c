/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/09/04 17:43:09 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* - Create observer thread and one thread per philosopher
- Wait for each thread to finish */
void	create_threads(t_config *config)
{
	int		i;
	t_philo	*p;

	i = 0;
	pthread_create(&config->observer_th, NULL, obs_routine, config);
	while (i < config->total_philo)
	{
		p = &config->philo_arr[i];
		pthread_create(&p->philo_th, NULL, philo_routine, p);
		i++;
	}
	config->start_time = getmilliseconds();
	i = 0;
	while (i < config->total_philo)
	{
		pthread_join(config->philo_arr[i].philo_th, NULL);
		i++;
	}
	pthread_join(config->observer_th, NULL);
}

int	main(int argc, char *argv[])
{
	int			status;
	t_config	config;

	if (argc <= 4)
		return (EXIT_FAILURE);
	if (!arg_validation(argc, argv))
		return (EXIT_FAILURE);
	status = init_config(&config, argc, argv);
	if (status < 0)
		return (cleanup(&config), EXIT_FAILURE);
	create_threads(&config);
	cleanup(&config);
	return (EXIT_SUCCESS);
}
