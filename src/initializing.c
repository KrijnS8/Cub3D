/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/15 15:35:17 by splattje      #+#    #+#                 */
/*   Updated: 2024/09/24 15:15:10 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @return a pointer to the t_map struct
 * @brief initializes the values for the map struct
 */
static t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (perror("Error\nMalloc failed4"), NULL);
	map->c_color = NULL;
	map->f_color = NULL;
	map->c_color_hex = 0;
	map->f_color_hex = 0;
	map->n_image_location = NULL;
	map->s_image_location = NULL;
	map->e_image_location = NULL;
	map->w_image_location = NULL;
	map->images = NULL;
	map->map = NULL;
	map->map_list = NULL;
	map->p_face = 0;
	map->p_x = 0;
	map->p_y = 0;
	return (map);
}

/**
 * @return a pointer to the t_data struct
 * @brief initializes the values for the main struct and all the sub structs 
 */
t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (perror("Error\nMalloc failed5"), NULL);
	data->map = init_map();
	if (data->map == NULL)
		return (free(data), NULL);
	data->mlx = NULL;
	data->win = NULL;
	data->height = 0;
	data->width = 0;
	return (data);
}
