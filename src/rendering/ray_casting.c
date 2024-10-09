/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:35:00 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 13:47:12 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include "cube.h"

#include <math.h>

double	my_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

t_point	create_point(double x, double y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	setup_ray(t_cast_config *cast, t_ray *ray, int i)
{
	ray->camera_x = 2 * i / NUM_RAYS - 1;
	ray->dir.x = cast->dir.x + cast->plane.x * ray->camera_x;
	ray->dir.y = cast->dir.y + cast->plane.y * ray->camera_x;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = my_abs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = my_abs(1 / ray->dir.y);
	ray->map_x = (int)cast->pos.x;
	ray->map_y = (int)cast->pos.y;
	ray->hit = false;
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (cast->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - cast->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (cast->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - cast->pos.y) * ray->delta_dist.y;
	}
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
	while (i < NUM_RAYS)
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
