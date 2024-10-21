/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 15:11:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/21 17:13:11 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include <math.h>

static int	get_line_width()
{
	static int	line_width = -1;

	if (line_width == -1)
		line_width = SCREEN_WIDTH / get_num_rays();
	return (line_width + 1);
}

void	render_ray(t_data *data, t_ray ray, int n_rays, int i, int location_rays)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	double	scale_factor;

	x = get_line_width() * (location_rays + i);
	y = (SCREEN_HEIGHT - ray.height) / 2;
	scale_factor = (double)data->map->img[ray.index].h / ray.height;
	dx = 0;
	dy = 0;
	while (dx < get_line_width())
	{
		while (dy < ray.height)
		{
			int	src_x = (data->map->img[ray.index].w / n_rays * i) + dx;
			int src_y = (int)dy * scale_factor;
			src_x = src_x % data->map->img[ray.index].w;
            src_y = src_y % data->map->img[ray.index].h;
			put_pixel_img(data->frame, x + dx, y + dy, get_pixel_img(data->map->img[ray.index], src_x, src_y));
			dy++;
		}
		dx++;
	}
}

void	render_wall(t_data *data, t_ray *rays, int n_rays, int location_rays)
{
	(void)data;
	int	i;

	i = 0;
	while (i < n_rays)
	{
		render_ray(data, rays[i], n_rays, i ,location_rays);
		i++;
	}
}

t_error	render_frame(t_data *data, t_ray *rays)
{
	int			i;
	int			j;
	t_ipoint	wall;

	clear_img(data->frame);
	i = 0;
	while (i < get_num_rays())
	{
		j = 0;
		wall.x = rays[i].map_x;
		wall.y = rays[i].map_y;
		while (rays[i + j].map_x == wall.x && rays[i + j].map_y == wall.y)
			j++;
		render_wall(data, &(rays[i]), j, i);
		i += j;
	}
	return (ERR_OK);
}
