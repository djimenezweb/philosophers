/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:31:59 by danielji          #+#    #+#             */
/*   Updated: 2025/10/26 15:33:23 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* - Read mutex-protected `stop_val` and return it
- If it's `0`, simulation should continue
- If it's `1`, simulation should stop */
int	get_stop(t_config *config)
{
	int	value;

	pthread_mutex_lock(&config->stop_mtx);
	value = config->stop_val;
	pthread_mutex_unlock(&config->stop_mtx);
	return (value);
}

/* Modify mutex-protected `last_lunch` */
void	set_last_lunch(t_philo *p)
{
	pthread_mutex_lock(&p->last_lunch_mtx);
	p->last_lunch = getmilliseconds();
	pthread_mutex_unlock(&p->last_lunch_mtx);
}

/* Modify mutex-protected `stop_val` */
void	set_stop(t_config *config, int value)
{
	pthread_mutex_lock(&config->stop_mtx);
	config->stop_val = value;
	pthread_mutex_unlock(&config->stop_mtx);
}
