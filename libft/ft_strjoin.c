/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:24:22 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/24 10:04:14 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (0);
	ft_strlcpy(output, s1, len + 1);
	ft_strlcat(output, s2, len + 1);
	return (output);
}
