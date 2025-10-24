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

/* - Create one thread per philosopher
- Wait for each thread to finish */
void	create_threads(t_config *config)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < config->total_philo)
	{
		p = &config->philo_arr[i];
		pthread_create(&p->thread, NULL, routine, p);
		printf("Created thread %d (philo %d)\n", i, i + 1);
		i++;
	}
	config->start_time = getmilliseconds();
	i = 0;
	while (i < config->total_philo)
	{
		pthread_join(config->philo_arr[i].thread, NULL);
		i++;
	}
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
