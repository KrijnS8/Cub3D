/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:40:31 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/25 08:37:05 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*sptr;

	sptr = s;
	while (n-- > 0)
	{
		if ((const unsigned char)*sptr == (unsigned char)c)
			return ((unsigned char *)sptr);
		sptr++;
	}
	return (NULL);
}
