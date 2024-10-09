/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:35:00 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 12:37:12 by kschelvi      ########   odam.nl         */
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

t_dda_config	cast_setup(t_data *data, t_cast_config *dda, t_ray *ray)
{
	(void)ray;
	dda->pos.x = data->map->player.p_x;
	dda->pos.y = data->map->player.p_y;
	dda->dir.x = cos(degree_to_radians(data->map->player.p_angle));
	dda->dir.y = cos()
	return (*dda);
}

// void get_image_index(t_dda_config *dda, t_ray *ray)
// {

// }

t_error cast_ray(t_data *data, t_ray *ray)
{
	t_dda_config	dda;
	
	dda_setup(data, &dda, ray);
	return (ERR_OK);
}
