/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:38:10 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 11:06:28 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philosophers.h"

/* Checks if passed arguments are valid numbers. */
int	arg_validation(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}