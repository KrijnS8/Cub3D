/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 10:50:30 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/09 11:08:38 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;

	duplicate = malloc(ft_strlen(s) + 1);
	if (duplicate != NULL)
		ft_strlcpy(duplicate, s, ft_strlen(s) + 1);
	return (duplicate);
}
