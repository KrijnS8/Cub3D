/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:43:45 by kschelvi          #+#    #+#             */
/*   Updated: 2024/10/02 13:30:34 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include "gameplay.h"

#include "cube.h"

void	update_screen(t_data *data, t_ray *rays)
{
	int		ray_number;
	int		x;
	int		y;
	int		next;

	ray_number = -1;
	while (++ray_number <= NUM_RAYS)
	{
		x = ray_number * (SCREEN_WIDTH / NUM_RAYS);
		y = -1;
		next = (ray_number + 1) * (SCREEN_WIDTH / NUM_RAYS);
		while (++y < rays[ray_number].line.height && y <= (SCREEN_HEIGHT - 127))
		{
			while (x < next)
				mlx_pixel_put(data->mlx, data->win, x++, y,
					data->map->c_color_hex);
			x = ray_number * (SCREEN_WIDTH / NUM_RAYS);
		}
		mlx_put_image_to_window(data->mlx, data->win, data->map->images[N_WALL], x, y);
		y += 254;
		while (++y <= (SCREEN_WIDTH))
		{
			while (x < next)
				mlx_pixel_put(data->mlx, data->win, x++, y,
					data->map->f_color_hex);
			x = ray_number * (SCREEN_WIDTH / NUM_RAYS);
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
			continue;
		}
		last_angle = degree_add(last_angle, int_to_degree(RAY_ANGLE_DELTA));
		rays[i].degree = last_angle;
		rays[i].line.num = i;
		i++;
	}
}

t_error	build_frame(t_data *data)
{
	void	*frame;
	t_ray	rays[NUM_RAYS];

	frame = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	init_rays(rays, data->map->player.p_angle.value);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		//printf("%f\n", rays[i].degree.value);
		cast_ray(data, &(rays[i]));
	}
	update_screen(data, rays);
	return (ERR_OK);
}
