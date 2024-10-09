/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frame.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:43:45 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 11:55:29 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include "gameplay.h"

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

	(void)rays;
	y = -1;
	while (++y <= SCREEN_HEIGHT)
	{
		x = -1;
		while (++x <= SCREEN_WIDTH)
		{
			counter = ((y / 256) * 8) + (x / 256);
			if (y < ((SCREEN_HEIGHT / 2) - 256))
				put_pixel_img(data->map->img[counter], x % 256, y % 256,
					data->map->c_color_hex);
			else if (y > ((SCREEN_HEIGHT / 2)))
				put_pixel_img(data->map->img[counter], x % 256, y % 256,
					data->map->f_color_hex);
			if (x > 254 && y > 254 && ((x % 255) == 0) && ((y % 255) == 0))
				mlx_put_image_to_window(data->mlx, data->win,
					data->map->img[counter].img_ptr, (x - 255), (y - 255));
		}
	}
}

void	init_rays(t_ray *rays, double p_angle)
{
	size_t		i;
	t_degree	last_angle;

	i = 0;
	while (i < NUM_RAYS)
	{
		if (i == 0)
		{
			rays[i].degree = double_to_degree(p_angle - FIELD_OF_VIEW / 2);
			last_angle = rays[i].degree;
			rays[i].line.num = i;
			i++;
			continue ;
		}
		last_angle = degree_add(last_angle, double_to_degree(RAY_ANGLE_DELTA));
		rays[i].degree = last_angle;
		rays[i].line.num = i;
		i++;
	}
}

t_error	build_frame(t_data *data)
{
	t_ray	rays[NUM_RAYS];

	init_rays(rays, data->map->player.p_angle.value);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		//printf("%f\n", rays[i].degree.value);
		cast_ray(data, &(rays[i]));
	}
	update_screen(data, rays);
	return (ERR_OK);
}
