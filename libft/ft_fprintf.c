/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 15:22:06 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/16 09:43:17 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_data_sort(va_list ap, const char *string, int i, int fd)
{
	int	amound_of_conv;

	amound_of_conv = 0;
	while (string[i])
	{
		if (string[i] == '%')
		{
			i++;
			if (string[i] == 'c' || string[i] == '%')
				amound_of_conv += ftf_putchar(ap, string[i], 1, fd);
			if (string[i] == 's')
				amound_of_conv += ftf_putstring(ap, fd);
			if (string[i] == 'p')
				amound_of_conv += ftf_put_ptr_to_str(ap, fd);
			if (string[i] == 'd' || string[i] == 'i')
				amound_of_conv += ftf_putnumber(ap, fd);
			if (string[i] == 'u' || string[i] == 'x' || string[i] == 'X')
				amound_of_conv += ftf_uint_to_str(ap, string[i], fd);
		}
		else
			amound_of_conv += ftf_putchar(ap, string[i], 0, fd);
		i++;
	}
	return (amound_of_conv);
}

int	ft_fprintf(int fd, const char *string, ...)
{
	va_list	ap;
	int		lenght;
	int		index;

	va_start(ap, string);
	index = 0;
	lenght = 0;
	lenght = ft_data_sort(ap, string, index, fd);
	va_end(ap);
	return (lenght);
}
