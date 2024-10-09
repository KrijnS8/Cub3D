/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:35:00 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 14:20:23 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include "cube.h"

#include <math.h>

t_point	create_point(double x, double y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}
}

t_error	ray_casting(t_data *data, t_cast_config *cast, t_ray *rays)
{
	int		i;

	i = 0;
	while (i < get_num_rays())
	{
		setup_ray(cast, &(rays[i]), i);
		dda(data, &(rays[i]));
		if (rays[i].side == 0)
			rays[i].distance = (rays[i].side_dist.x - rays[i].delta_dist.x);
		else
			rays[i].distance = (rays[i].side_dist.y - rays[i].delta_dist.y);
		rays[i].height = (int)(SCREEN_HEIGHT / rays[i].distance);
		printf("Distance: %f\t%f\n", rays[i].distance, rays[i].height);
		i++;
	}
	return (ERR_OK);
}
