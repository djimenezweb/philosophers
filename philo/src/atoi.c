/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:32:00 by danielji          #+#    #+#             */
/*   Updated: 2025/08/21 12:48:58 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Converts the initial portion of the string pointed to by `str` to `int`.
The string may begin with an arbitrary amount of white space.
The remainder of the string is converted to a long value stopping at the
first character which is not a valid digit in the given base.
Returns the converted value or `-1` on error. */
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
