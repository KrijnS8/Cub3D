/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:30:39 by splattje          #+#    #+#             */
/*   Updated: 2024/10/28 15:38:58 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	set_map_object(t_map_list **map, char ***result, int index)
{
	if (ft_strncmp((*map)->line, "DOOR", 4) == 0)
	{
		(*result)[index] = set_map_info(*map, 5);
		*map = (*map)->next->next;
		(*result)[++index] = set_map_info(*map, 2);
	}
	else
	{
		*map = (*map)->next;
		(*result)[index] = set_map_info(*map, 2);
	}
	return (index);
}
