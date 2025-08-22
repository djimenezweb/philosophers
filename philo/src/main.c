/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 11:06:53 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_config	config;
	//t_philo		*array;

	if (argc <= 4)
		return (EXIT_FAILURE);
	if (!arg_validation(argc, argv))
		return (EXIT_FAILURE);
	config = init_config(argc, argv);
	create_threads(config);
	free(config.philo_array);
	return (EXIT_SUCCESS);
}
