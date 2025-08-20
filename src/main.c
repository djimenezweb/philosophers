/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/08/20 20:42:59 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

/* TO DO: Parse valid numbers (exclude text, negative numbers, etc) */
t_config	init_config(int argc, char *argv[])
{
	t_config	config;

	config.number = ft_atoi(argv[1]);
	config.tt_die = ft_atoi(argv[2]);
	config.tt_eat = ft_atoi(argv[3]);
	config.tt_sleep = ft_atoi(argv[4]);
	if (argc >= 6)
		config.max_loops = ft_atoi(argv[5]);
	else
		config.max_loops = -1;
	return (config);
}

t_philo	init_philo(int id)
{
	t_philo	p;

	p.id = id;
	return (p);
}

t_philo	*init_array(int	n)
{
	int 	i;
	t_philo	*array;

	array = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!array)
		return (NULL);
	i = 0;
	while (i < n)
	{
		array[i] = init_philo(i + 1);
		i++;
	}
	return (array);
}

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