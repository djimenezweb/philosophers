/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:44:37 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 11:18:56 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philosophers.h"

/* void	*routine(void *arg)
{
	t_config	*c;

	c = (t_config *)arg;
	timestamp(1, "says hello");
	return (NULL);
} */

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	timestamp(p->id, "says hello");
	return (NULL);
}

void	create_threads(t_config config)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < config.number)
	{
		config.philo_array[i].thread = thread;
		pthread_create(&thread, NULL, routine, (void *)&config.philo_array[i]);
		pthread_join(thread, NULL);
		i++;
	}
}
