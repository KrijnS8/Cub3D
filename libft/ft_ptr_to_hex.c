/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptr_to_hex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 14:15:49 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/16 09:41:23 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_hex_digits(void *ptr)
{
	unsigned long long	intptr;
	int					count;

	intptr = (unsigned long long)ptr;
	count = 0;
	while (intptr > 0)
	{
		intptr >>= 4;
		count++;
	}
	if (count > 0)
		return (count);
	else
		return (1);
}

static char	*reverse(char *str, int size)
{
	int		i;
	int		length;
	char	temp;

	i = 0;
	length = size / 2;
	while (i < length)
	{
		temp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = temp;
		i++;
	}
	return (str);
}

char	*ptr_to_hex(void *ptr)
{
	int					buffer_size;
	char				*hex_buffer;
	int					i;
	unsigned long long	digit;

	buffer_size = count_hex_digits(ptr) + 1;
	hex_buffer = (char *)malloc(buffer_size);
	i = 0;
	while (1)
	{
		digit = (unsigned long long)ptr & 0xF;
		ptr = (void *)((unsigned long long)ptr >> 4);
		if (digit < 10)
			hex_buffer[i++] = '0' + digit;
		else
			hex_buffer[i++] = 'a' + (digit - 10);
		if ((unsigned long long)ptr == 0)
			break ;
	}
	hex_buffer[i] = '\0';
	hex_buffer = reverse(hex_buffer, i);
	return (hex_buffer);
}
