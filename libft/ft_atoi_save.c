/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:59:35 by splattje          #+#    #+#             */
/*   Updated: 2024/06/25 16:19:06 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_save(char *charp, int *number)
{
	long	convert;
	int		index;
	int		sign;

	convert = 0;
	index = 0;
	sign = 1;
	while (ft_iswhitespace(charp[index]))
		index++;
	if (charp[index] == '-' || charp[index] == '+')
	{
		if (charp[index] == '-')
			sign = -1;
		index++;
	}
	while (ft_isdigit(charp[index]))
	{
		convert = convert * 10 + (charp[index] - '0');
		if (convert * sign > INT_MAX || convert * sign < INT_MIN)
			return (-1);
		index++;
	}
	*number = (int)convert;
	return (0);
}
