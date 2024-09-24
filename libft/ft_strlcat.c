/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:25:03 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/24 08:50:21 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	dst_index;

	dst_index = 0;
	while (dst[dst_index] != '\0' && dst_index < size)
		dst_index++;
	index = dst_index;
	while (src[dst_index - index] && dst_index + 1 < size)
	{
		dst[dst_index] = src[dst_index - index];
		dst_index++;
	}
	if (index < size)
		dst[dst_index] = '\0';
	return (index + ft_strlen(src));
}
