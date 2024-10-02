/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:35:00 by kschelvi          #+#    #+#             */
/*   Updated: 2024/10/02 08:44:23 by splattje         ###   ########.fr       */
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

t_dda_config	dda_setup(t_data *data, t_dda_config *dda, t_ray *ray)
{
	dda->pos = create_point(data->map->player.p_x, data->map->player.p_y);
	dda->start = dda->pos;
	dda->dir.x = cos(degree_to_radian(ray->degree));
	dda->dir.y = sin(degree_to_radian(ray->degree));
	if (dda->dir.x >= 0)
		dda->step_x = 1;
	else
		dda->step_x = -1;
	if (dda->dir.y >= 0)
		dda->step_y = 1;
	else
		dda->step_y = -1;
	if (dda->dir.x == 0)
		dda->side_dist.x = 1e30;
	else
		dda->side_dist.x = fabs(1.0 / dda->dir.x);
	if (dda->dir.y == 0)
		dda->side_dist.y = 1e30;
	else
		dda->side_dist.y = fabs(1.0 / dda->dir.y);
	dda->delta.x = dda->step_x * dda->side_dist.x;
	dda->delta.y = dda->step_y * dda->side_dist.y;
	return (*dda);
}

t_error cast_ray(t_data *data, t_ray *ray)
{
	t_dda_config	dda;
	int				map_x;
	int				map_y;

	dda_setup(data, &dda, ray);
	map_x = (int)dda.start.x;
	map_y = (int)dda.start.y;
	while (map_x >= 0 && map_x < data->width && map_y >= 0 && map_y < data->height)
	{
		if (data->map->map[map_y][map_x] == 1)
		{
			dda.distance = sqrt((dda.pos.x - dda.start.x) * (dda.pos.x - dda.start.x) + (dda.pos.y - dda.start.y) * (dda.pos.y - dda.start.y));
			ray->distance = dda.distance;
			break ;
		}
		if (dda.delta.x < dda.delta.y)
		{
			map_x += dda.step_x;
			dda.delta.x += dda.side_dist.x;
		}
		else
		{
			map_y += dda.step_y;
			dda.delta.y += dda.side_dist.y;
		}
		dda.pos.x += dda.dir.x;
		dda.pos.y += dda.dir.y;
	}
	return (ERR_OK);
}
