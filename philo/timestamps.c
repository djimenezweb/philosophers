/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:51:42 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 12:55:14 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Cualquier cambio de estado de un filósofo debe tener el siguiente formato:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Reemplaza timestamp_in_ms con la marca de tiempo actual en milisegundos
y X con el numero del filósofo. */

/* Prints change in status and current milliseconds since the start 
TODO: Lock mutex to make printf safer */
void	timestamp(int id, char *str, long start)
{
	long	ms;

	ms = getmilliseconds() - start;
	printf("%ld %d %s\n", ms, id, str);
}

/* Return current Epoch time in milliseconds */
long	getmilliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/* Suspend execution for an interval in milliseconds */
void	ft_sleep_ms(int ms)
{
	usleep(ms * 1000);
}
