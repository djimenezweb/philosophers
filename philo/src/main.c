/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 12:55:44 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_config	config;

	if (argc <= 4)
		return (EXIT_FAILURE);
	if (!arg_validation(argc, argv))
		return (EXIT_FAILURE);
	config = init_config(argc, argv);
	config.philo_array = init_array(&config, config.total_philo);
	config.start_time = getmilliseconds();
	create_threads(&config);
	free(config.philo_array);
	/* Destroy mutexes before free
		for (int i = 0; i < config.total_philo; i++)
			pthread_mutex_destroy(&config.forks[i]);
	*/
	free(config.forks);
	return (EXIT_SUCCESS);
}
