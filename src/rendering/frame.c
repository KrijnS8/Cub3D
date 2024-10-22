/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frame.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:43:45 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/22 16:11:14 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include <math.h>

/**
 * @param data pointer to the main data struct (t_data)
 * @param cast pointer to the cast config struct (t_cast_config)
 * @brief Initializes a cast config struct using the data from a data struct
 */
void	cast_setup(t_data *data, t_cast_config *cast)
{
	double	right_x;
	double	right_y;

	cast->pos.x = data->map->player.p_x + 0.5;
	cast->pos.y = data->map->player.p_y + 0.5;
	cast->dir.x = cos(degree_to_radian(data->map->player.p_angle));
	cast->dir.y = sin(degree_to_radian(data->map->player.p_angle));
	right_x = -cast->dir.y;
	right_y = cast->dir.x;
	cast->plane.x = right_x / sqrt(right_x * right_x + right_y * right_y);
	cast->plane.y = right_y / sqrt(right_x * right_x + right_y * right_y);
}

/**
 * @param data pointer to the main data struct (t_data)
 * @brief builds a frame using the current game status
 * @return an error struct (t_error)
 */
int	build_frame(t_data *data)
{
	t_ray			rays[(int)(FIELD_OF_VIEW / RAY_ANGLE_DELTA)];
	t_cast_config	cast;

	cast_setup(data, &cast);
	ray_casting(data, &cast, rays);
	render_frame(data, rays);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img_ptr, 0, 0);
	return (ERR_OK);
}
