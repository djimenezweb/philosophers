/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:44:37 by danielji          #+#    #+#             */
/*   Updated: 2025/08/21 09:47:38 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *) arg;
	printf("Philosopher %d says hello\n", p->id);
	return (NULL);
}

void	create_threads(int n, t_philo	*array)
{
	int			i;
	pthread_t	id;

	i = 0;
	while (i < n)
	{
		array[i].thread = id;
		pthread_create(&id, NULL, routine, (void *) &array[i]);
		pthread_join(id, NULL);
		i++;
	}
}
