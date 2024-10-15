/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:11:48 by kschelvi          #+#    #+#             */
/*   Updated: 2024/10/23 10:02:42 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include <math.h>

/**
 * @return line width calculated by screen width and number of rays
 */
static int	get_line_width(void)
{
	static int	line_width = -1;

	if (line_width == -1)
		line_width = SCREEN_WIDTH / get_num_rays();
	return (line_width);
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param rays pointer to an array of ray structs (t_ray)
 * @param i index of current ray in rays array
 * @param location_rays location of the current rays in original rays array
 * @brief renders a single ray
 */
static void	render_ray(t_data *data, t_ray *rays, int i, int location_rays)
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	t_ipoint	src;

	x = get_line_width() * (location_rays + i);
	y = (SCREEN_HEIGHT - rays[i].height) / 2;
	dx = 0;
	while (dx < get_line_width())
	{
		dy = 0;
		while (dy < rays[i].height)
		{
			src.x = rays[i].wall_x * data->map->img[rays[i].index].w;
			src.y = (int)dy * \
				(double)data->map->img[rays[i].index].h / rays[i].height;
			src.x = src.x % data->map->img[rays[i].index].w;
			src.y = src.y % data->map->img[rays[i].index].h;
			put_pixel_img(data->frame, x + dx, y + dy, \
				get_pixel_img(data->map->img[rays[i].index], src.x, src.y));
			dy++;
		}
		dx++;
	}
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param rays pointer to an array of ray structs (t_ray)
 * @param n_rays length of rays array
 * @param location_rays location of the current rays in original rays array
 * @brief renders a single wall
 */
static void	render_wall(t_data *data, t_ray *rays, \
							int n_rays, int location_rays)
{
	int	i;

	i = 0;
	while (i < n_rays)
	{
		render_ray(data, rays, i, location_rays);
		i++;
	}
}

/**
 * @param data pointer to the main data struct (t_data)
 * @brief draws floor and ceiling onto frame
 */
static void	draw_background(t_data *data)
{
	int		y;
	int		x;
	t_img	src;

	y = 0;
	src = data->frame;
	while (y < src.h)
	{
		x = 0;
		while (x < src.w)
		{
			if (y < src.h / 2)
				put_pixel_img(src, x, y, data->map->c_color_hex);
			else
				put_pixel_img(src, x, y, data->map->f_color_hex);
			x++;
		}
		y++;
	}
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param rays pointer to an array of ray structs (t_ray)
 * @brief renders a single frame using the information from the rays array
 * @return an error code, rendered frame is stored in data struct
 */
t_error	render_frame(t_data *data, t_ray *rays)
{
	int			i;
	int			j;
	t_ipoint	wall;

	draw_background(data);
	i = 0;
	while (i < get_num_rays())
	{
		j = 0;
		wall.x = rays[i].map_x;
		wall.y = rays[i].map_y;
		while (i + j < get_num_rays() && \
				rays[i + j].map_x == wall.x && rays[i + j].map_y == wall.y)
			j++;
		render_wall(data, &(rays[i]), j, i);
		i += j;
	}
	return (ERR_OK);
}
