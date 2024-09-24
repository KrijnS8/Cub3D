/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 15:22:06 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/16 09:41:29 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_data_sort(va_list ap, const char *string, int i)
{
	int	amound_of_conv;

	amound_of_conv = 0;
	while (string[i])
	{
		if (string[i] == '%')
		{
			i++;
			if (string[i] == 'c' || string[i] == '%')
				amound_of_conv += ft_putchar(ap, string[i], 1);
			if (string[i] == 's')
				amound_of_conv += ft_putstring(ap);
			if (string[i] == 'p')
				amound_of_conv += ft_put_ptr_to_str(ap);
			if (string[i] == 'd' || string[i] == 'i')
				amound_of_conv += ft_putnumber(ap);
			if (string[i] == 'u' || string[i] == 'x' || string[i] == 'X')
				amound_of_conv += ft_uint_to_str(ap, string[i]);
		}
		else
			amound_of_conv += ft_putchar(ap, string[i], 0);
		i++;
	}
	return (amound_of_conv);
}

int	ft_printf(const char *string, ...)
{
	va_list	ap;
	int		lenght;
	int		index;

	va_start(ap, string);
	index = 0;
	lenght = 0;
	lenght = ft_data_sort(ap, string, index);
	va_end(ap);
	return (lenght);
}
