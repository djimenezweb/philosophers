/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/08/21 09:47:05 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_config	config;
	t_philo		*array;

	if (argc <= 4)
		return (0);
	config = init_config(argc, argv);
	if (config.number > 0)
		array = init_array(config.number);
	else
		return (0);
/*	int i = 0;
	while (i < config.number)
	{
		printf("id = %d\n", array[i].id);
		i++;
	} */
	create_threads(config.number, array);
	free(array);
	return (0);
}
