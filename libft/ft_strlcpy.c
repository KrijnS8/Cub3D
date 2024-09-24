/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:26:49 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/25 09:39:11 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	while (*src && index + 1 < size)
	{
		*dst++ = *src++;
		++index;
	}
	if (index < size)
		*dst = 0;
	while (*src++)
		++index;
	return (index);
}
