/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uint_to_hex_uplow.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 15:01:42 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/16 09:41:19 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(unsigned int n)
{
	int	length;
	int	num;

	if (n == 0)
		length = 1;
	else
		length = 0;
	num = n;
	while (n > 0)
	{
		n >>= 4;
		length++;
	}
	return (length);
}

static char	get_char(int nibble, int uplow)
{
	if (nibble < 10)
		return ('0' + nibble);
	else
	{
		if (uplow == 1)
			return ('a' + nibble - 10);
		else
			return ('A' + nibble - 10);
	}
}

char	*uint_to_hex_uplow(unsigned int num, int uplow)
{
	unsigned int	length;
	unsigned int	n;
	char			*hex_str;
	int				index;
	int				nibble;

	if (uplow > 1)
		return (NULL);
	length = get_length(num);
	hex_str = (char *)malloc(length + 1);
	if (hex_str == NULL)
		return (NULL);
	hex_str = ft_memset(hex_str, 0, length + 1);
	index = length - 1;
	n = num;
	if (n == 0)
		hex_str[0] = '0';
	while (n > 0)
	{
		nibble = n & 0xF;
		hex_str[index] = get_char(nibble, uplow);
		n >>= 4;
		index--;
	}
	return (hex_str);
}
