/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:51:23 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 16:58:56 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "my_error.h"

/**
 * @param map a 2d char array of the map
 * @param y the current y value we are in the map
 * @param x the current x value we are in the map
 * @param height the max height of the map
 * @return false if a open space is not adjacent to an open space or wall
 * @brief checks if open spaces in the map are adjacent to other open spaces
 * or walls
 */
bool	floor_fill(char **map, int y, int x, int height)
{
	if (map[y][x] == '0')
	{
		if (y - 1 < 0 || y + 1 >= height || x - 1 < 0
			|| x + 1 > (int)ft_strlen(map[y]))
			return (print_error(ERR_FLOOR), false);
		if (!check_postion(map, y - 1, x))
			return (false);
		if (!check_postion(map, y + 1, x))
			return (false);
		if (!check_postion(map, y, x - 1))
			return (false);
		if (!check_postion(map, y, x + 1))
			return (false);
		if (!check_postion(map, y - 1, x - 1))
			return (false);
		if (!check_postion(map, y + 1, x + 1))
			return (false);
		if (!check_postion(map, y + 1, x - 1))
			return (false);
		if (!check_postion(map, y - 1, x + 1))
			return (false);
	}
	return (true);
}

/**
 * @param map_array a 2d array with the map data
 * @param map a double pointer to the map struct (t_map)
 * @return true if one player is found false if none or more
 * @brief checks where the player is located and stores it in the map struct.
 * And the way the player is facing
 */
static bool	player_check(char **map_array, t_map **map)
{
	int	line;
	int	index;

	line = -1;
	while (map_array[++line] != NULL)
	{
		index = -1;
		while (map_array[line][++index] != '\0')
		{
			if (map_array[line][index] == 'N' || map_array[line][index] == 'S'
				|| map_array[line][index] == 'E'
				|| map_array[line][index] == 'W')
			{
				if ((*map)->player.p_face != 0)
					return (print_error(ERR_PLAYER), false);
				(*map)->player.p_face = map_array[line][index];
				(*map)->player.p_angle = char_to_degree((*map)->player.p_face);
				(*map)->player.p_x = index;
				(*map)->player.p_y = line;
			}
		}
	}
	if ((*map)->player.p_face != 0)
		return (true);
	return (print_error(ERR_PLAYER), false);
}

/**
 * @param map a double pointer to the map struct (t_map)
 * @return true if the image files can be opened and read
 * @brief checks if the image file excists, opened, and read
 */
static bool	check_wall_file(t_map **map)
{
	int	fd;

	fd = open((*map)->n_image_location, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), (false));
	close(fd);
	fd = open((*map)->s_image_location, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), (false));
	close(fd);
	fd = open((*map)->w_image_location, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), (false));
	close(fd);
	fd = open((*map)->e_image_location, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), (false));
	close(fd);
	if ((*map)->door_file_location != NULL)
	{
		if (!check_door_file(map))
			return (false);
	}
	return (true);
}

/**
 * @param rgb_string the string holding the rgb value
 * @return returnst the value as hex, -1 if the number was not in rgb range
 * @brief convets the rgb color to the hex veriant;
 */
static int	floor_ceiling_rgb(char *rgb_string)
{
	t_rgb	rgb;
	int		index;

	index = -1;
	rgb.r = 0;
	if (ft_strlen(rgb_string) < 5 || ft_strlen(rgb_string) > 11)
		return (print_error(ERR_RGB), -1);
	while (ft_isdigit(rgb_string[++index]))
		rgb.r = rgb.r * 10 + (rgb_string[index] - '0');
	if (rgb.r < 0 || rgb.r > 255)
		return (print_error(ERR_RGB_BOUND), -1);
	rgb.g = 0;
	while (ft_isdigit(rgb_string[++index]))
		rgb.g = rgb.g * 10 + (rgb_string[index] - '0');
	if (rgb.g < 0 || rgb.g > 255)
		return (print_error(ERR_RGB_BOUND), -1);
	rgb.b = 0;
	while (ft_isdigit(rgb_string[++index]))
		rgb.b = rgb.b * 10 + (rgb_string[index] - '0');
	if (rgb.b < 0 || rgb.b > 255)
		return (print_error(ERR_RGB_BOUND), -1);
	if (rgb_string[index] != '\0')
		return (print_error(ERR_RGB), -1);
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

/**
 * @param map a double pointer to the map struct (t_map)
 * @param height the height of the map
 * @return true if only one player is in the map and the map has a valid floor
 * @brief checks if the map contains one player and if the floor is valid
 */
bool	check_map(t_map **map, t_data *data)
{
	int		y;
	size_t	x;

	if (!player_check((*map)->map, map))
		return (false);
	(*map)->map[(int)(*map)->player.p_y][(int)(*map)->player.p_x] = '0';
	y = -1;
	while ((*map)->map[++y] != NULL)
	{
		x = -1;
		if (!check_door_floor(map, x, y, data))
			return (false);
	}
	(*map)->map[(int)(*map)->player.p_y][(int)(*map)->player.p_x]
		= (*map)->player.p_face;
	if (!check_wall_file(map))
		return (false);
	(*map)->c_color_hex = floor_ceiling_rgb((*map)->c_color);
	(*map)->f_color_hex = floor_ceiling_rgb((*map)->f_color);
	if ((*map)->c_color_hex == -1 || (*map)->f_color_hex == -1)
		return (false);
	if (!set_images(&data))
		return (false);
	return (true);
}
