/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:45:29 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 10:08:12 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "my_error.h"

bool	check_door_file(t_map **map)
{
	int	fd;

	fd = open((*map)->door_file_location, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), false);
	close(fd);
	return (true);
}

bool	check_door_floor(t_map **map, int x, int y, t_data *data)
{
	while ((*map)->map[y][++x] != '\0')
	{
		if (!floor_fill((*map)->map, y, x, data->height))
			return (false);
		if ((*map)->map[y][x] == 'D')
			if (!check_door(map, data, x, y))
				return (false);
	}
	return (true);
}

bool	check_postion(char **map, int y, int x)
{
	if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'D')
		return (print_error(ERR_FLOOR), false);
	return (true);
}
