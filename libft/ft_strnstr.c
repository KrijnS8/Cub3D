/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 10:46:33 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/21 08:57:02 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	index;

	if (!ft_strlen(little))
		return ((char *)big);
	if (!ft_strlen(big) || len < ft_strlen(little))
		return (NULL);
	little_len = ft_strlen(little);
	index = 0;
	while (big[index] && len >= little_len)
	{
		if (ft_strncmp((big + index), little, little_len) == 0)
			return ((char *)(big + index));
		index++;
		len--;
	}
	return (NULL);
}
