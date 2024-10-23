/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:35:17 by splattje          #+#    #+#             */
/*   Updated: 2024/10/23 10:42:33 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "my_error.h"
#include "rendering.h"

/**
 * @return the initialized player struct
 * @brief sets default value for the player struct
 */
static t_player	init_player(void)
{
	t_player	player;

	player.p_face = 0;
	player.p_x = 0;
	player.p_y = 0;
	player.move_fb = 0;
	player.move_lr = 0;
	player.looking = 0;
	return (player);
}

/**
 * @return a pointer to the t_map struct
 * @brief initializes the values for the map struct
 */
static t_map	*init_map(void)
{
	t_map	*map;
	int		index;

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
	map->door_file_location = NULL;
	map->map = NULL;
	map->map_list = NULL;
	index = -1;
	while (++index < 5)
		map->img[index].img_ptr = NULL;
	map->player = init_player();
	map->doors = NULL;
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
	data->frame.addr = NULL;
	data->frame.img_ptr = NULL;
	return (data);
}
