/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:47:53 by splattje          #+#    #+#             */
/*   Updated: 2024/10/23 10:42:09 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
 * @param data the main data struct  (t_data)
 * @param images the images needed to be freed
 * @brief frees all the images)
 */
static void	free_images(t_data *data, t_img images[5])
{
	int	index;

	if (data->frame.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->frame.img_ptr);
	index = -1;
	if (images != NULL)
	{
		while (images[++index].img_ptr != NULL && index < 5)
			mlx_destroy_image(data->mlx, images[index].img_ptr);
	}
}

/**
 * @param map a pointer to the t_map struct
 * @brief frees the map data struct
 */
void	free_map(t_map *map)
{
	t_door	*tmp;

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
	if (map->door_file_location != NULL)
		free(map->door_file_location);
	while (map->doors != NULL)
	{
		tmp = map->doors->next;
		free(map->doors);
		map->doors = tmp;
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
			free_map(data->map);
			if (data->map->img[0].img_ptr != NULL)
				free_images(data, data->map->img);
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
