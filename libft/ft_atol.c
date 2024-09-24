/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 11:33:13 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/27 13:34:17 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *string)
{
	long	number;
	long	index;
	int		sign;

	index = 0;
	while (ft_iswhitespace(string[index]))
		index++;
	sign = 1;
	if (string[index] == '+' || string[index] == '-')
	{
		if (string[index] == '-')
			sign = -1;
		index++;
	}
	number = 0;
	while (ft_isdigit(string[index]))
	{
		number = number * 10 + (string[index] - '0');
		index++;
	}
	return (number * sign);
}
