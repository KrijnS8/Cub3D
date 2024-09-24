/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 09:42:54 by splattje      #+#    #+#                 */
/*   Updated: 2023/10/13 10:01:53 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		index;
	t_list	*position;

	index = 0;
	position = lst;
	while (position != NULL)
	{
		position = position->next;
		index++;
	}
	return (index);
}
