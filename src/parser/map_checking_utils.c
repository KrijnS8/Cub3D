/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:42:23 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 16:59:55 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "my_error.h"

static t_door	*set_door(int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	if (door == NULL)
		return (print_error(ERR_MALLOC), NULL);
	door->x = x;
	door->y = y;
	door->state = D_CLOSE;
	door->next = NULL;
	return (door);
}

static bool	check_door_valid(t_map *map, t_data *data, int x, int y)
{
	if (y - 1 < 0 || y + 1 >= data->height || x - 1 < 0
		|| x + 1 > (int)ft_strlen(map->map[y]))
		return (print_error(ERR_MAP_BOUND), false);
	if (map->map[y + 1][x] == '1' && map->map[y - 1][x] == '1'
		&& map->map[y][x + 1] == '0' && map->map[y][x - 1] == '0')
		return (true);
	if (map->map[y + 1][x] == '0' && map->map[y - 1][x] == '0'
		&& map->map[y][x + 1] == '1' && map->map[y][x - 1] == '1')
		return (true);
	return (print_error(ERR_DOOR), false);
}

bool	check_door(t_map **map, t_data *data, int x, int y)
{
	t_door	*new;
	t_door	*tmp;

	if ((*map)->map[y][x] == 'D')
	{
		if (!check_door_valid(*map, data, x, y))
			return (false);
		new = set_door(x, y);
		if (new == NULL)
			return (false);
		if (data->map->doors == NULL)
			data->map->doors = new;
		else
		{
			tmp = data->map->doors;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (true);
}

t_door	*door_exists(t_data *data, int x, int y)
{
	t_door	*door;

	door = data->map->doors;
	while (door != NULL)
	{
		if (y == door->y && x == door->x)
			break ;
		door = door->next;
	}
	return (door);
}
