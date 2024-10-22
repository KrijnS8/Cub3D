/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 15:11:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/22 14:07:07 by kschelvi      ########   odam.nl         */
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
	return (line_width);
}

void	render_ray(t_data *data, t_ray *rays, int n_rays, int i, int location_rays)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	double	scale_factor;

	x = get_line_width() * (location_rays + i);
	y = (SCREEN_HEIGHT - rays[i].height) / 2;
	scale_factor = (double)data->map->img[rays[i].index].h / rays[i].height;
	dx = 0;
	
	while (dx < get_line_width())
	{
		dy = 0;
		while (dy < rays[i].height)
		{
			// int	src_x = (data->map->img[ray.index].w / n_rays * i) + dx;
			int src_x = (data->map->img[rays[i].index].w * (i / (double)n_rays));
			int src_y = (int)dy * scale_factor;
			src_x = src_x % data->map->img[rays[i].index].w;
            src_y = src_y % data->map->img[rays[i].index].h;
			put_pixel_img(data->frame, x + dx, y + dy, get_pixel_img(data->map->img[rays[i].index], src_x, src_y));
			dy++;
		}
		dx++;
	}
}

// double get_x_coordinate(t_data *data, t_ray ray)
// {
//     (void)data;
//     double x_hit;

//     if (ray.side == 0) // Vertical wall hit
//     {
//         x_hit = ray.side_dist.x;
//     }
//     else // Horizontal wall hit
//     {
//         x_hit = ray.side_dist.y * ray.dir.x / ray.dir.y;
//     }

//     // Normalize the x_hit to be between 0 and 1
//     x_hit = fmod(x_hit + 1.0, 1.0); // Adjust for the starting point

//     return x_hit;
// }


void	render_wall(t_data *data, t_ray *rays, int n_rays, int location_rays)
{
	(void)data;
	int	i;

	i = 0;
	while (i < n_rays)
	{
		render_ray(data, rays, n_rays, i ,location_rays);
		//printf("wall_x: %f\n", get_x_coordinate(data, rays[i]));
		i++;
	}
}

void	draw_background(t_data *data)
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
		while (i + j < get_num_rays() && rays[i + j].map_x == wall.x && rays[i + j].map_y == wall.y)
			j++;
		render_wall(data, &(rays[i]), j, i);
		i += j;
		//break ;
	}
	return (ERR_OK);
}
