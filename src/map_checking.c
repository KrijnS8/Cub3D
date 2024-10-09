/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checking.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 09:51:23 by splattje      #+#    #+#                 */
/*   Updated: 2024/10/09 11:55:22 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @param map a 2d char array of the map
 * @param y the current y value we are in the map
 * @param x the current x value we are in the map
 * @param height the max height of the map
 * @return false if a open space is not adjacent to an open space or wall
 * @brief checks if open spaces in the map are adjacent to other open spaces
 * or walls
 */
static bool	floor_fill(char **map, int y, int x, int height)
{
	if (map[y][x] == '0')
	{
		if (y - 1 < 0 || y + 1 > height || x - 1 < 0
			|| x + 1 > (int)ft_strlen(map[y]))
			return (false);
		if (map[y - 1][x] != '1' && map[y - 1][x] != '0')
			return (false);
		if (map[y + 1][x] != '1' && map[y + 1][x] != '0')
			return (false);
		if (map[y][x - 1] != '1' && map[y][x - 1] != '0')
			return (false);
		if (map[y][x + 1] != '1' && map[y][x + 1] != '0')
			return (false);
		if (map[y - 1][x - 1] != '1' && map[y - 1][x - 1] != '0')
			return (false);
		if (map[y + 1][x + 1] != '1' && map[y + 1][x + 1] != '0')
			return (false);
		if (map[y + 1][x - 1] != '1' && map[y + 1][x - 1] != '0')
			return (false);
		if (map[y - 1][x + 1] != '1' && map[y - 1][x + 1] != '0')
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
					return (false);
				(*map)->player.p_face = map_array[line][index];
				(*map)->player.p_angle = char_to_degree((*map)->player.p_face);
				(*map)->player.p_x = index;
				(*map)->player.p_y = line;
			}
		}
	}
	if ((*map)->player.p_face != 0)
		return (true);
	return (false);
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
		return (perror("Error\nfailed to open file\n"), (false));
	close(fd);
	fd = open((*map)->s_image_location, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nfailed to open file\n"), (false));
	close(fd);
	fd = open((*map)->w_image_location, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nfailed to open file\n"), (false));
	close(fd);
	fd = open((*map)->e_image_location, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nfailed to open file\n"), (false));
	close(fd);
	return (true);
}

/**
 * @param rgb_string the string holding the rgb value
 * @return returnst the value as hex
 * @brief convets the rgb color to the hex veriant;
 */
static int	floor_ceiling_rgb(char *rgb_string)
{
	int	r;
	int	g;
	int	b;
	int	index;
	int	hex_value;

	index = -1;
	r = 0;
	while (rgb_string[++index] != ',' && rgb_string[index] != '\0')
		r = r * 10 + (rgb_string[index] - '0');
	g = 0;
	while (rgb_string[++index] != ',' && rgb_string[index] != '\0')
		g = g * 10 + (rgb_string[index] - '0');
	b = 0;
	while (rgb_string[++index] != ',' && rgb_string[index] != '\0')
		b = b * 10 + (rgb_string[index] - '0');
	hex_value = (r << 16) | (g << 8) | b;
	return (hex_value);
}

/**
 * @param map a double pointer to the map struct (t_map)
 * @param height the height of the map
 * @return true if only one player is in the map and the map has a valid floor
 * @brief checks if the map contains one player and if the floor is valid
 */
bool	check_map(t_map **map, int height, t_data *data)
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
		while ((*map)->map[y][++x] != '\0')
		{
			if (!floor_fill((*map)->map, y, x, height))
				return (false);
		}
	}
	(*map)->map[(int)(*map)->player.p_y][(int)(*map)->player.p_x]
		= (*map)->player.p_face;
	if (!check_wall_file(map))
		return (false);
	(*map)->c_color_hex = floor_ceiling_rgb((*map)->c_color);
	(*map)->f_color_hex = floor_ceiling_rgb((*map)->f_color);
	if (!set_images(&data))
		return (false);
	return (true);
}
