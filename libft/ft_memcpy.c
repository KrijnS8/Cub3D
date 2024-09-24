/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:59:43 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/19 09:52:36 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destination;
	char	*source;

	if (!dest && !src)
		return (dest);
	destination = (char *)dest;
	source = (char *)src;
	while (n != 0)
	{
		*destination++ = *source++;
		n--;
	}
	return (dest);
}
