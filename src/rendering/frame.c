/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:45 by kschelvi          #+#    #+#             */
/*   Updated: 2024/10/07 13:07:34 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include "gameplay.h"

#include "cube.h"

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr
			+ (y * img.line_len) + (x * img.bpp / 8))));
}

void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

void	update_screen(t_data *data, t_ray *rays)
{
	int		x;
	int		y;
	int		counter;

	(void)rays;
	counter = 1;
	y = 0;
	while (y <= SCREEN_HEIGHT)
	{
		x = 0;
		while (x <= SCREEN_WIDTH)
		{
			if (y < ((SCREEN_HEIGHT / 2) - 128))
				put_img_to_img(data->map->img[counter], data->map->img[40],
					0, 0);
			if (y > ((SCREEN_HEIGHT / 2) + 128))
				put_img_to_img(data->map->img[counter], data->map->img[41],
					0, 0);
			mlx_put_image_to_window(data->mlx, data->win,
				data->map->img[counter].img_ptr, x, y);
			x = x + 256;
			counter++;
		}
		y = y + 256;
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
		last_angle = degree_add(last_angle, int_to_degree(RAY_ANGLE_DELTA));
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
