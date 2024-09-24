/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:57:33 by splattje          #+#    #+#             */
/*   Updated: 2024/09/24 15:05:07 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static void	*set_img(void *mlx, char *map_location)
{
	int		height;
	int		width;
	void	*img;

	height = 256;
	width = 256;
	img = mlx_xpm_file_to_image(mlx, map_location, &width, &height);
	return (img);
}

int	set_wall_image(void *mlx, t_map *map)
{
	map->images = malloc(sizeof(void *) * 4);
	if (map->images == NULL)
		return (1);
	map->images[N_WALL] = set_img(mlx, map->n_image_location);
	if (map->images[N_WALL] == NULL)
		return (1);
	map->images[S_WALL] = set_img(mlx, map->s_image_location);
	if (map->images[S_WALL] == NULL)
		return (1);
	map->images[W_WALL] = set_img(mlx, map->w_image_location);
	if (map->images[W_WALL] == NULL)
		return (1);
	map->images[E_WALL] = set_img(mlx, map->e_image_location);
	if (map->images[E_WALL] == NULL)
		return (1);
	return (0);
}
