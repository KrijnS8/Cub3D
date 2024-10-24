/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 15:11:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/24 15:29:38 by kschelvi      ########   odam.nl         */
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
static void	render_ray(t_data *data, t_ray *rays, int i)
{
	int			x;
	int			y;
	int			line_start;
	t_ipoint	src;

	x = get_line_width() * i;
	line_start = (SCREEN_HEIGHT - rays[i].height) / 2;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < line_start)
			put_line_to_image(data->frame, create_ipoint(x, y), get_line_width(), data->map->c_color_hex);
		else if (y > line_start + rays[i].height - 1)
			put_line_to_image(data->frame, create_ipoint(x, y), get_line_width(), data->map->f_color_hex);
		else
		{
			src.x = rays[i].wall_x * data->map->img[rays[i].index].w;
			src.y = (int)(y - line_start) * \
				(double)data->map->img[rays[i].index].h / rays[i].height;
			put_line_to_image(data->frame, create_ipoint(x, y), get_line_width(), get_pixel_img(data->map->img[rays[i].index], src.x, src.y));
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

	i = 0;
	while (i < get_num_rays())
	{
		render_ray(data, rays, i);
		i++;
	}
	return (ERR_OK);
}
