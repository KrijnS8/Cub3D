/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:27:27 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/03 08:50:27 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
