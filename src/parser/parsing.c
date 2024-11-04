/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:08:51 by splattje          #+#    #+#             */
/*   Updated: 2024/11/04 11:44:13 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "my_error.h"

/**
 * @param fd the file descripter of the file being read
 * @param data a double pointer to the main data stuct (t_data)
 * @return true if all went well, false on malloc error
 * @brief through the help of get_next_line we read into
 * the file and add it to the map data as linked list
 */
bool	read_map(int fd, t_data **data)
{
	char		*line;
	char		*trimmed;
	t_map_list	*node;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed = ft_strtrim(line, "\n");
		if (trimmed == NULL)
			break ;
		free(line);
		node = new_map_list(trimmed);
		if (node == NULL)
			return (free_map((*data)->map), false);
		map_list_add_back(data, node);
	}
	if (line != NULL)
		free(line);
	return (true);
}

/**
 * @param map the linked list to the map data
 * @param data pointer to the main data struct
 * @return a double char pointer with the map data, or NULL on failure
 * @brief converts the map data linked list into a 2D array
 */
char	**map_to_array(t_map_list *map, t_data **data)
{
	int		index;
	char	**map_array;
	int		length;

	index = -1;
	while (++index < 8)
		map = map->next;
	map_array = (char **)ft_calloc(sizeof(char *), (*data)->height + 1);
	if (map_array == NULL)
		return (print_error(ERR_MALLOC), NULL);
	index = -1;
	while (map != NULL)
	{
		map_array[++index] = ft_calloc(sizeof(char), ((*data)->width + 1));
		if (map_array[index] == NULL)
			return (print_error(ERR_MALLOC), NULL);
		ft_strlcpy(map_array[index], map->line, ft_strlen(map->line) + 1);
		length = -1;
		while (((int)ft_strlen(map->line) + ++length) < (*data)->width)
			map_array[index][map->line_size + length] = ' ';
		map = map->next;
	}
	return (map_array);
}

/**
 * @param map a pointer to the map linked list struct (t_map_list)
 * @param index the starting postion for the double array
 * @return a array with map data
 * @brief gets the names of the image locations for the walls and RGB
 * colors for the F and C 
 */
char	**set_map_values(t_map_list *map, int index)
{
	char		**result;
	int			max;

	max = set_max(map);
	result = ft_calloc(sizeof(char *), max);
	if (result == NULL)
		return (print_error(ERR_MALLOC), NULL);
	while (++index < max)
	{
		if (index == -1)
			return (free_2d_array(result), NULL);
		if (index < 4)
		{
			if (!set_wall_textures(&map, &result, index))
				return (free_2d_array(result), NULL);
		}
		else if (index == 4)
			index = set_map_object(&map, &result, 4);
		else
			result[index] = set_map_info(map, 2);
		if (result[index] == NULL)
			return (free_2d_array(result), NULL);
		map = map->next;
	}
	return (result);
}

/**
 * @param map a double pointer to the map struct (t_map)
 * @return ture on success, false on error
 * @brief checks if the map has the write values inside it
 */
bool	parse_map(t_data **data)
{
	char	**map_array;
	char	**map_values;
	int		index;

	get_map_height_width(data);
	map_values = set_map_values(((*data)->map->map_list), -1);
	if (map_values == NULL)
		return (false);
	map_array = map_to_array((*data)->map->map_list, data);
	if (map_array == NULL)
		return (false);
	(*data)->map->n_image_location = map_values[0];
	(*data)->map->s_image_location = map_values[1];
	(*data)->map->w_image_location = map_values[2];
	(*data)->map->e_image_location = map_values[3];
	index = 4;
	if (ft_strncmp(map_values[index], "images", 6) == 0)
		(*data)->map->door_file_location = map_values[index++];
	(*data)->map->f_color = map_values[index++];
	(*data)->map->c_color = map_values[index];
	(*data)->map->map = map_array;
	free(map_values);
	return (true);
}

/**
 * @param input a char pointer holding the name of the given map
 * @param data double pointer to the main data struct (t_data)
 * @return true on success, false on error
 * @brief checks the given map and gives it
 * a file descriptor and parses the data 
 */
bool	parse_input(char *input, t_data **data)
{
	size_t	lenght;
	int		fd;

	lenght = ft_strlen(input);
	if (ft_strncmp(input + (lenght - 4), ".cub", 4) != 0)
		return (print_error(ERR_EXTENTION), false);
	fd = open(input, O_RDWR);
	if (fd == -1)
		return (print_error(ERR_OPEN), false);
	if (!read_map(fd, &(*data)))
	{
		close(fd);
		return (false);
	}
	close(fd);
	if (!parse_map(data))
		return (false);
	if (!check_map(&(*data)->map, *data))
		return (false);
	return (true);
}
