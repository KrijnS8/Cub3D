/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:20:51 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/31 16:31:33 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n, int base)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n && ++count)
		n /= base;
	return (count);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*output;
	const char	*digits;

	digits = "0123456789";
	len = ft_numlen(n, 10);
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (0);
	output[len] = 0;
	if (n == 0)
		output[0] = '0';
	if (n < 0)
		output[0] = '-';
	while (n)
	{
		if (n > 0)
			output[--len] = digits[n % 10];
		else
			output[--len] = digits[n % 10 * -1];
		n /= 10;
	}
	return (output);
}
