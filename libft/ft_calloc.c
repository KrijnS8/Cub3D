/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 17:56:30 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/31 16:38:06 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void				*memory;
	unsigned long long	total;

	if (nmemb == 0 || size == 0)
	{
		memory = malloc(1);
		if (memory == NULL)
			return (NULL);
		ft_bzero(memory, 1);
		return (memory);
	}
	total = size * nmemb;
	if (total / size == nmemb)
	{
		memory = malloc(total);
		if (memory == NULL)
			return (NULL);
		ft_bzero(memory, total);
		return (memory);
	}
	return (NULL);
}
