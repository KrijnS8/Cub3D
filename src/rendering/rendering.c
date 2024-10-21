/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 15:11:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/21 16:35:39 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include <math.h>

double get_x_coordinate(t_data *data, t_ray ray)
{
	(void)data;
    double x_hit;

    if (ray.side == 0) // Vertical wall hit
    {
        x_hit = ray.side_dist.x; // Directly use side_dist.x
    }
    else // Horizontal wall hit
    {
        x_hit = ray.side_dist.y * ray.dir.x / ray.dir.y; // Calculate based on direction
    }

    // Normalize the x_hit to be between 0 and 1
    x_hit = fmod(x_hit, 1.0);
	//printf("%f\n", x_hit);
    return x_hit * data->map->img[0].w;
}

void	add_line(t_data *data, t_ray ray, int i)
{
	   static int line_width = -1;
    int x;
    int y;
    int dx;
    int dy;
    double scale_factor;

    if (line_width == -1)
        line_width = SCREEN_WIDTH / get_num_rays();

    x = line_width * i;
    y = (SCREEN_HEIGHT - ray.height) / 2;

    scale_factor = (double)data->map->img[N_WALL].h / ray.height;

    for (dx = 0; dx < line_width; dx++)
    {
        for (dy = 0; dy < ray.height; dy++)
        {
            int texture_x = (int)get_x_coordinate(data, ray);
            texture_x = texture_x % data->map->img[N_WALL].w;

            int texture_y = (int)((dy / (double)ray.height) * data->map->img[N_WALL].h);
            texture_y = texture_y % data->map->img[N_WALL].h;

            int pixel_color = get_pixel_img(data->map->img[N_WALL], texture_x, texture_y);
            put_pixel_img(data->frame, x + dx, y + dy, pixel_color);
        }
    }
}

t_error	render_frame(t_data *data, t_ray *rays)
{
	int	i;

	clear_img(data->frame);
	i = 0;
	while (i < get_num_rays())
	{
		add_line(data, rays[i], i);
		i++;
	}
	
	return (ERR_OK);
}
