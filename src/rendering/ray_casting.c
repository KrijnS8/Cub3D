/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:35:00 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/21 13:17:24 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include "cube.h"

#include <math.h>

/**
 * @param x x value
 * @param y y value
 * @return A point struct (t_dpoint)
 */
t_dpoint	create_point(double x, double y)
{
	t_dpoint	point;

	point.x = x;
	point.y = y;
	return (point);
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param ray pointer to a ray struct (t_ray)
 * @brief Performs dda algorithm on the given ray
 */
static void	dda(t_data *data, t_ray *ray)
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

/**
 * @param ray pointer to a ray struct (t_ray)
 * @brief Calculates the distance height and side an intersected ray has hit
 */
static void	calculate_render_data(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->distance = (ray->side_dist.x - ray->delta_dist.x);
		if (ray->dir.x < 0)
			ray->index = W_WALL;
		else
			ray->index = E_WALL;
	}
	else
	{
		ray->distance = (ray->side_dist.y - ray->delta_dist.y);
		if (ray->dir.y < 0)
			ray->index = S_WALL;
		else
			ray->index = N_WALL;
	}
	ray->height = (int)(SCREEN_HEIGHT / ray->distance);
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param cast pointer to a cast config struct (t_cast_config)
 * @param rays pointer to an uninitialized array of rays
 * @return An error struct (t_error), ray information will be stored in
 * the original array
 * @brief Performs a raycasting operation from the current player position
 */
t_error	ray_casting(t_data *data, t_cast_config *cast, t_ray *rays)
{
	int		i;

	i = 0;
	while (i < get_num_rays())
	{
		setup_ray(cast, &(rays[i]), i);
		dda(data, &(rays[i]));
		calculate_render_data(&(rays[i]));
		//printf("Distance: %f\tHeight: %f\tSide: %d\n", rays[i].distance, rays[i].height, rays[i].index);
		i++;
	}
	return (ERR_OK);
}
