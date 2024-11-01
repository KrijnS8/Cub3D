/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:57:33 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 09:31:18 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "rendering.h"
#include "my_error.h"

/**
 * @var img the new empty image
 * @param data the main data struct (t_data)
 * @return returns an new empty image, returns early if img_ptr is NULL
 * @brief makes an new empty image
 */
static t_img	new_empty_image(t_data *data, int width, int height)
{
	t_img	img;

	img.w = width;
	img.h = height;
	img.img_ptr = mlx_new_image(data->mlx, img.w, img.h);
	if (img.img_ptr == NULL)
		return (print_error(ERR_MLX), img);
	img.addr = mlx_get_data_addr(img.img_ptr, (&img.bpp),
			&(img.line_len), &(img.endian));
	return (img);
}

/**
 * @var img the new empty image
 * @param mlx_ptr pointer to mlx struct
 * @param image_location path to image
 * @return returns an new image, returns early if img_ptr is NULL
 * @brief creates a new image
 */
static t_img	new_image(void *mlx_ptr, char *image_location)
{
	t_img	img;

	img.img_ptr = mlx_xpm_file_to_image(mlx_ptr, image_location, \
										&img.w, &img.h);
	if (img.img_ptr == NULL)
		return (print_error(ERR_MLX), img);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bpp), \
									&(img.line_len), &(img.endian));
	return (img);
}

/**
 * @var index the image index
 * @param data pointer to the main data struct (t_data)
 * @return false if img_ptr is null true once all the images are made
 * @brief makes the images needed to fill the screen
 */
bool	set_images(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	tmp->map->img[N_WALL] = new_image(tmp->mlx, tmp->map->n_image_location);
	if (tmp->map->img[N_WALL].img_ptr == NULL)
		return (false);
	tmp->map->img[S_WALL] = new_image(tmp->mlx, tmp->map->s_image_location);
	if (tmp->map->img[S_WALL].img_ptr == NULL)
		return (false);
	tmp->map->img[W_WALL] = new_image(tmp->mlx, tmp->map->w_image_location);
	if (tmp->map->img[W_WALL].img_ptr == NULL)
		return (false);
	tmp->map->img[E_WALL] = new_image(tmp->mlx, tmp->map->e_image_location);
	if (tmp->map->img[E_WALL].img_ptr == NULL)
		return (false);
	if (tmp->map->door_file_location != NULL)
	{
		tmp->map->img[DOOR] = new_image(tmp->mlx, tmp->map->door_file_location);
		if (tmp->map->img[DOOR].img_ptr == NULL)
			return (false);
	}
	tmp->frame = new_empty_image(*data, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (tmp->frame.img_ptr == NULL)
		return (false);
	return (true);
}
