/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftf_output.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 10:00:06 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/16 09:43:30 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ftf_putchar(va_list ap, char c, int inputplace, int fd)
{
	char	ch;

	if (inputplace == 1)
	{
		if (c == 'c')
		{
			ch = va_arg(ap, int);
			ft_putchar_fd(ch, fd);
			return (1);
		}
		else
		{
			ft_putchar_fd('%', fd);
			return (1);
		}
	}
	else
	{
		ft_putchar_fd(c, fd);
		return (1);
	}
}

int	ftf_putstring(va_list ap, int fd)
{
	char	*str;

	str = NULL;
	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	ftf_put_ptr_to_str(va_list ap, int fd)
{
	char	*str;
	void	*ptr;
	int		length;

	ptr = va_arg(ap, void *);
	str = fptr_to_hex(ptr);
	if (str != NULL)
	{
		if (*str == '0' && ft_strlen(str) == 1)
		{
			free(str);
			str = "(nil)";
			ft_putstr_fd(str, fd);
			return (5);
		}
		else
		{
			length = ft_strlen(str);
			write(fd, "0x", 2);
			ft_putstr_fd(str, fd);
			free(str);
			return (length + 2);
		}
	}
	return (0);
}

int	ftf_putnumber(va_list ap, int fd)
{
	int		num;
	char	*str;
	int		length;

	str = NULL;
	num = va_arg(ap, int);
	str = ft_itoa(num);
	if (str != NULL)
	{
		length = ft_strlen(str);
		ft_putstr_fd(str, fd);
		free(str);
		return (length);
	}
	return (0);
}

int	ftf_uint_to_str(va_list ap, char c, int fd)
{
	unsigned int	un_num;
	char			*str;
	int				length;

	str = NULL;
	if (c == 'u')
	{
		un_num = va_arg(ap, unsigned int);
		str = fuitostr(un_num);
	}
	else if (c == 'x' || c == 'X')
	{
		un_num = va_arg(ap, unsigned int);
		str = fuint_to_hex_uplow(un_num, c == 'x');
	}
	if (str != NULL)
	{
		length = ft_strlen(str);
		ft_putstr_fd(str, fd);
		free(str);
		return (length);
	}
	return (0);
}
