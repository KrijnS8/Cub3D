/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:57:33 by splattje          #+#    #+#             */
/*   Updated: 2024/10/07 13:00:36 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

static void	set_image_pixel(t_img *img, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= img->w)
	{
		x = -1;
		while (++x <= img->h)
			put_pixel_img(*img, x, y, color);
	}
}

static t_img	new_empty_image(t_data *data)
{
	t_img	img;

	img.w = 256;
	img.h = 256;
	img.img_ptr = mlx_new_image(data->mlx, img.w, img.h);
	if (img.img_ptr == NULL)
		return (img);
	img.addr = mlx_get_data_addr(img.img_ptr, (&img.bpp),
			&(img.line_len), &(img.endian));
	return (img);
}

static t_img	new_image(t_data *data, t_image_index i_index)
{
	t_img	img;

	if (i_index == N_WALL)
		img.img_ptr = mlx_xpm_file_to_image(data->mlx,
				data->map->n_image_location, &img.w, &img.h);
	else if (i_index == S_WALL)
		img.img_ptr = mlx_xpm_file_to_image(data->mlx,
				data->map->s_image_location, &img.w, &img.h);
	else if (i_index == E_WALL)
		img.img_ptr = mlx_xpm_file_to_image(data->mlx,
				data->map->e_image_location, &img.w, &img.h);
	else
		img.img_ptr = mlx_xpm_file_to_image(data->mlx,
				data->map->w_image_location, &img.w, &img.h);
	if (img.img_ptr == NULL)
		return (img);
	img.addr = mlx_get_data_addr(img.img_ptr, (&img.bpp),
			&(img.line_len), &(img.endian));
	return (img);
}

bool	set_images(t_data **data)
{
	int	index;

	index = -1;
	while (++index < 42)
	{
		if (index >= 40)
			(*data)->map->img[index] = new_empty_image(*data);
		else
			(*data)->map->img[index] = new_image(*data, N_WALL);
		if ((*data)->map->img[index].img_ptr == NULL)
			return (false);
		if (index == 40)
			set_image_pixel(&(*data)->map->img[index],
				(*data)->map->c_color_hex);
		if (index == 41)
			set_image_pixel(&(*data)->map->img[index],
				(*data)->map->f_color_hex);
	}
	return (true);
}
