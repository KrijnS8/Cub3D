/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:47:53 by splattje          #+#    #+#             */
/*   Updated: 2024/09/24 15:02:58 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

/**
 * @param list the linked list with of the map data
 * @brief frees the map liked list that holds the map file data
 */
static void	free_map_list(t_map_list *list)
{
	t_map_list	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		free(list->line);
		free(list);
		list = tmp;
	}
}

/**
 * @param map a pointer to the t_map struct
 * @brief frees the map data struct
 */
void	free_map(t_map *map, void *mlx)
{
	enum e_image_index	index;

	free_map_list(map->map_list);
	if (map->map != NULL)
		free_2d_array(map->map);
	if (map->c_color != NULL)
		free(map->c_color);
	if (map->f_color != NULL)
		free(map->f_color);
	if (map->n_image_location != NULL)
		free(map->n_image_location);
	if (map->s_image_location != NULL)
		free(map->s_image_location);
	if (map->w_image_location != NULL)
		free(map->w_image_location);
	if (map->e_image_location != NULL)
		free(map->e_image_location);
	if (map->images != NULL)
	{
		index = -1;
		while (++index < 4)
			mlx_destroy_image(mlx, map->images[index]);
		free(map->images);
	}
}

/**
 * @param data a pointer to the main data struct (t_data)
 * @brief frees the main data struct and all the sub structs inside it
 */
void	free_data(t_data *data)
{
	if (data != NULL)
	{
		if (data->map != NULL)
		{
			free_map(data->map, data->mlx);
			free(data->map);
		}
		if (data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx != NULL)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		free(data);
	}
}

/**
 * @param array a double pointer will alloced data
 * @brief frees the 2d array with all the sub strings in it
 */
void	free_2d_array(char **array)
{
	int	index;

	index = 0;
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
}
