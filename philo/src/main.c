/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/09/04 17:43:09 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	if (create_threads(&config) != 0)
	{
		// TO DO: free something else?
		cleanup(&config);
		return (EXIT_FAILURE);
	}
	cleanup(&config);
	return (EXIT_SUCCESS);
}
