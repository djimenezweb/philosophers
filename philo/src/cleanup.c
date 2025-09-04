/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:42:58 by danielji          #+#    #+#             */
/*   Updated: 2025/09/04 17:43:09 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philosophers.h"

void	cleanup(t_config *config)
{
	int	i;
	int	n;

	i = 0;
	n = config->total_philo;
	if (config->philo_array)
	{
		free(config->philo_array);
		config->philo_array = NULL;
	}
	while (i < n)
	{
		pthread_mutex_destroy(&config->forks[i]);
		i++;
	}
	if (config->forks)
	{
		free(config->forks);
		config->forks = NULL;
	}
}