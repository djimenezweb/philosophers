/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/08/21 12:26:32 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_config	config;
	t_philo		*array;

	if (argc <= 4)
		return (EXIT_FAILURE);
	config = init_config(argc, argv);
	if (config.number < 0)
		return (EXIT_FAILURE);
	array = init_array(config.number);
	create_threads(config.number, array);
	free(array);
	return (EXIT_SUCCESS);
}
