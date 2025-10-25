/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:10:34 by danielji          #+#    #+#             */
/*   Updated: 2025/10/25 13:10:39 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*obs_routine(void *arg)
{
	t_config	*config;

	config = (t_config *)arg;
	(void)config;
	
	return (NULL);
}