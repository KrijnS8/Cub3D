/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:45 by kschelvi          #+#    #+#             */
/*   Updated: 2024/10/15 12:52:57 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include "gameplay.h"
#include "degree.h"
#include <math.h>

/**
 * @param img img struct countaining image info
 * @param x the x position in the image
 * @param y the y position in the image
 * @return returns the current pixel form the image
 */
unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr
			+ (y * img.line_len) + (x * img.bpp / 8))));
}

/**
 * @param x the x position on screen
 * @param y the y position of screen
 * @param data pointer to the main data struct
 * @param rays pointer to all the rays
 * @brief looks at what color the pixel needs to be and fills it.
 */
static void	put_pixel(int x, int y, t_data *data, t_ray *rays)
{
	int	counter;
	int	rest;
	int	ray;

	counter = ((y / 256) * 8) + (x / 256);
	if (counter > 40)
		counter = 40;
	ray = x / (SCREEN_WIDTH / get_num_rays());
	if (ray > get_num_rays() - 1)
		ray = get_num_rays() - 1;
	rest = (SCREEN_HEIGHT - rays[ray].height) / 2;
	if (y < rest)
		put_pixel_img(data->map->img[counter], x % 256, y % 256,
			data->map->c_color_hex);
	else if (y > rays[ray].height)
		put_pixel_img(data->map->img[counter], x % 256, y % 256,
			data->map->f_color_hex);
	else
		put_pixel_img(data->map->img[counter], x % 256, y % 256, 
			get_pixel_img(data->map->img[41 + rays[ray].index],
			x % 256, y % 256));
}

/**
 * @var x the x cordinate of the screen
 * @var y the y cordinate of the screen
 * @var counter which image in de image array we need 
 * 	(on srceen the images are portrait 5 across 8 down)
 * @param data  pointer the main data struct holding all data (t_data)
 * @param rays all the rays and there info (t_ray)
 * @brief looks wat each color each pixel on the screen needs and sets that,
 * fills the screen with the images.
 */
void	update_screen(t_data *data, t_ray *rays)
{
	int	x;
	int	y;
	int	counter;

	y = -1;
	while (++y <= SCREEN_HEIGHT)
	{
		x = -1;
		while (++x <= SCREEN_WIDTH)
		{
			counter = ((y / 256) * 8) + (x / 256);
			if (counter > 40)
				counter = 40;
			put_pixel(x, y, data, rays);
			if (x > 254 && y > 254 && ((x % 255) == 0) && ((y % 255) == 0))
				mlx_put_image_to_window(data->mlx, data->win,
					data->map->img[counter].img_ptr, (x - 255), (y - 255));
		}
	}
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param cast pointer to the cast config struct (t_cast_config)
 * @brief Initializes a cast config struct using the data from a data struct
 */
void	cast_setup(t_data *data, t_cast_config *cast)
{
	double	right_x;
	double	right_y;

	cast->pos.x = data->map->player.p_x;
	cast->pos.y = data->map->player.p_y;
	cast->dir.x = cos(degree_to_radian(data->map->player.p_angle));
	cast->dir.y = cos(degree_to_radian(data->map->player.p_angle));
	right_x = -cast->dir.y;
	right_y = cast->dir.x;
	cast->plane.x = right_x / sqrt(right_x * right_x + right_y * right_y);
	cast->plane.y = right_y / sqrt(right_x * right_x + right_y * right_y);
}

/**
 * @param data pointer to the main data struct (t_data)
 * @brief builds a frame using the current game status
 * @return an error struct (t_error)
 */
t_error	build_frame(t_data *data)
{
	t_ray			rays[FIELD_OF_VIEW / RAY_ANGLE_DELTA];
	t_cast_config	cast;

	cast_setup(data, &cast);
	ray_casting(data, &cast, rays);
	update_screen(data, rays);
	return (ERR_OK);
}
