/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:35:00 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/11/04 11:52:50 by kschelvi      ########   odam.nl         */
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
t_dpoint	create_dpoint(double x, double y)
{
	t_dpoint	point;

	point.x = x;
	point.y = y;
	return (point);
}

/**
 * @param x x value
 * @param y y value
 * @return A point struct (t_ipoint)
 */
t_ipoint	create_ipoint(double x, double y)
{
	t_ipoint	point;

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
	t_door	*door;

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
		if (data->map->map[ray->map_y][ray->map_x] == 'D')
		{
			door = door_exists(data, ray->map_x, ray->map_y);
			if (door->state != D_OPEN)
				ray->hit = 2;
		}
		else if (data->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}
}

/**
 * @param player pointer to a player struct (t_player)
 * @param ray pointer to a ray struct (t_ray)
 * @brief Calculates the distance height and side an intersected ray has hit
 */
static void	calculate_render_data(t_player *player, t_ray *ray)
{
	double	wall_distance;

	if (ray->hit == 2)
		ray->index = DOOR;
	if (ray->side == 0)
	{
		ray->distance = (ray->side_dist.x - ray->delta_dist.x);
		if (ray->dir.x < 0 && ray->index != DOOR)
			ray->index = E_WALL;
		else if (ray->index != DOOR)
			ray->index = W_WALL;
		wall_distance = player->p_y + 0.5 + (ray->distance * ray->dir.y);
		ray->wall_x = fmod(wall_distance, 1);
	}
	else
	{
		ray->distance = (ray->side_dist.y - ray->delta_dist.y);
		if (ray->dir.y < 0 && ray->index != DOOR)
			ray->index = S_WALL;
		else if (ray->index != DOOR)
			ray->index = N_WALL;
		wall_distance = player->p_x + 0.5 + (ray->distance * ray->dir.x);
		ray->wall_x = fmod(wall_distance, 1);
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
		rays[i].index = 0;
		calculate_render_data(&data->map->player, &(rays[i]));
		i++;
	}
	return (ERR_OK);
}
