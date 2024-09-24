/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:43:54 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/21 09:02:21 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*string;
	int			index;

	string = s;
	index = ft_strlen(s);
	if ((unsigned char)c == 0)
		return ((char *)(s + index));
	while (&s[index] >= string)
	{
		if (s[index] == (unsigned char)c)
			return ((char *)(s + index));
		index--;
	}
	return (0);
}
