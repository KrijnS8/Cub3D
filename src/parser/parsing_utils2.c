/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:30:39 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 09:33:43 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "my_error.h"

int	set_map_object(t_map_list **map, char ***result, int index)
{
	if (ft_strncmp((*map)->line, "DOOR", 4) == 0)
	{
		(*result)[index] = set_map_info(*map, 5);
		*map = (*map)->next->next;
		if (ft_strncmp((*map)->line, "F", 1) != 0)
			return (print_error(ERR_MAP_ORDER), -2);
		(*result)[++index] = set_map_info(*map, 2);
	}
	else
	{
		*map = (*map)->next;
		if (ft_strncmp((*map)->line, "F", 1) != 0)
			return (print_error(ERR_MAP_ORDER), -2);
		(*result)[index] = set_map_info(*map, 2);
	}
	return (index);
}

bool	set_wall_textures(t_map_list **map, char ***result, int index)
{
	if (index == 0 && ft_strncmp((*map)->line, "NO ", 3) == 0)
		(*result)[index] = set_map_info(*map, 3);
	else if (index == 1 && ft_strncmp((*map)->line, "SO ", 3) == 0)
		(*result)[index] = set_map_info(*map, 3);
	else if (index == 2 && ft_strncmp((*map)->line, "WE ", 3) == 0)
		(*result)[index] = set_map_info(*map, 3);
	else if (index == 3 && ft_strncmp((*map)->line, "EA ", 3) == 0)
		(*result)[index] = set_map_info(*map, 3);
	else
		return (print_error(ERR_MAP_ORDER), false);
	return (true);
}

int	set_max(t_map_list *map)
{
	int	max;

	if (ft_strncmp(map->next->next->next->next->line, "DOOR", 4) == 0)
		max = 7;
	else
		max = 6;
	return (max);
}
