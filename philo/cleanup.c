/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:42:58 by danielji          #+#    #+#             */
/*   Updated: 2025/09/04 17:43:09 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Destroy initialized mutexes and free allocated memory */
void	cleanup(t_config *config)
{
	int	i;
	int	n;

	i = 0;
	n = config->total_philo;
	while (i < n)
	{
		pthread_mutex_destroy(&config->philo_arr[i].fork);
		i++;
	}
	free(config->philo_arr);
	pthread_mutex_destroy(&config->stop_mtx);
	config->philo_arr = NULL;
}
