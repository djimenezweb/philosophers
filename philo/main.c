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

/* - Wait for philosopher and observer threads to finish
- Call `cleanup` if thread join fails */
void	join_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->total_philo)
	{
		if (pthread_join(config->philo_arr[i].philo_th, NULL) != 0)
			cleanup(config);
		i++;
	}
	if (pthread_join(config->observer_th, NULL) != 0)
		cleanup(config);
}

/* - Create observer thread
- Create one thread per philosopher
- Call `cleanup` if thread creation fails
- Set starting time after they are all created */
void	create_threads(t_config *config)
{
	int		i;
	t_philo	*p;

	i = 0;
	if (pthread_create(&config->observer_th, NULL, obs_routine, config) != 0)
		cleanup(config);
	while (i < config->total_philo)
	{
		p = &config->philo_arr[i];
		if (pthread_create(&p->philo_th, NULL, philo_routine, p) != 0)
			cleanup(config);
		i++;
	}
	config->start_time = getmilliseconds();
}

int	main(int argc, char *argv[])
{
	t_config	config;

	if (arg_validation(argc, argv) < 0)
		return (EXIT_FAILURE);
	if (init_config(&config, argc, argv) < 0)
		return (cleanup(&config), EXIT_FAILURE);
	create_threads(&config);
	join_threads(&config);
	cleanup(&config);
	return (EXIT_SUCCESS);
}
