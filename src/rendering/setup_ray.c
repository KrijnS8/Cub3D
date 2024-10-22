/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_ray.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 14:04:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/22 16:05:44 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @return The amount of rays in the current FOV
 */
int	get_num_rays(void)
{
	static int	num_rays = -1;

	if (num_rays == -1)
		num_rays = (FIELD_OF_VIEW / RAY_ANGLE_DELTA);
	return (num_rays);
}

/**
 * @return Returns the absolute value of d
 */
static double	my_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

/**
 * @param ray pointer to a ray struct (t_ray)
 * @brief Initializes the delta distance of the given ray
 */
static void	setup_delta(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = my_abs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = my_abs(1 / ray->dir.y);
}

/**
 * @param cast pointer to a cast config struct (t_cast_config)
 * @param ray pointer to a ray struct (t_ray)
 * @brief Initializs the side distance and step values of the given ray
 */
static void	setup_side_step(t_cast_config *cast, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = \
			(cast->pos.x - (double)ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = \
			((double)ray->map_x + 1.0 - cast->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = \
			(cast->pos.y - (double)ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = \
			((double)ray->map_y + 1.0 - cast->pos.y) * ray->delta_dist.y;
	}
}

/**
 * @param cast pointer to a cast config struct (t_cast_config)
 * @param ray pointer to a ray struct (t_ray)
 * @param num number of the current ray
 * @brief Initializes the given ray struct
 */
void	setup_ray(t_cast_config *cast, t_ray *ray, int num)
{
	ray->camera_x = 2.0 * (double)num / (double)get_num_rays() - 1.0;
	ray->dir.x = cast->dir.x + cast->plane.x * ray->camera_x;
	ray->dir.y = cast->dir.y + cast->plane.y * ray->camera_x;
	ray->map_x = (int)cast->pos.x;
	ray->map_y = (int)cast->pos.y;
	ray->hit = false;
	setup_delta(ray);
	setup_side_step(cast, ray);
}
