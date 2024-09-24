/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitostr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:09:21 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/16 09:41:14 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(unsigned int number)
{
	int	length;

	if (number == 0)
		length = 1;
	else
		length = 0;
	while (number > 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*uitostr(unsigned int num)
{
	int				num_digit;
	char			*str;
	int				i;

	num_digit = get_length(num);
	str = (char *)malloc((num_digit + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	i = num_digit - 1;
	while (i >= 0)
	{
		str[i] = '0' + (num % 10);
		num /= 10;
		i--;
	}
	str[num_digit] = '\0';
	return (str);
}
