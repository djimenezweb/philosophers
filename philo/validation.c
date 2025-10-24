/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:38:10 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 12:55:50 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Convert the initial portion of the string pointed to by `str` to `int`.
Return the converted value or `-1` on error. */
int	ft_atoi(const char *str)
{
	long	nbr;

	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		nbr = (nbr * 10) + *str - '0';
		str++;
	}
	return ((int)nbr);
}

/* Return `1` if program arguments are valid numbers. */
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
