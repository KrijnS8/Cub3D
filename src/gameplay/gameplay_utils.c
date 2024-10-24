/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameplay_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 15:32:14 by splattje      #+#    #+#                 */
/*   Updated: 2024/10/24 16:18:35 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "gameplay.h"
#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

void	do_dirctional_calculations(t_data *data, double *dx, double *dy)
{
	if (data->map->player.move_fb != 0)
	{
		*dx += cos(degree_to_radian(data->map->player.p_angle))
			* -data->map->player.move_fb * PLAYER_SPEED;
		*dy += sin(degree_to_radian(data->map->player.p_angle))
			* -data->map->player.move_fb * PLAYER_SPEED;
	}
	if (data->map->player.move_lr != 0)
	{
		*dx += cos(degree_to_radian(data->map->player.p_angle) + (M_PI / 2.0))
			* data->map->player.move_lr * PLAYER_SPEED;
		*dy += sin(degree_to_radian(data->map->player.p_angle) + (M_PI / 2.0))
			* data->map->player.move_lr * PLAYER_SPEED;
	}
}

void	move(t_door *doors, t_data *data, double dx, double dy)
{
	if (doors != NULL)
	{
		if (doors->state == D_OPEN)
		{
			data->map->player.p_x += dx;
			data->map->player.p_y += dy;
		}
	}
	else
	{
		data->map->player.p_x += dx;
		data->map->player.p_y += dy;
	}
}

void	open_close_door(t_data *data, t_door *door)
{
	(void)data;
	if (door->state == D_CLOSE)
	{
		door->state = D_CHANGE;
		// render open and close door
		door->state = D_OPEN;
	}
	else if (door->state == D_OPEN)
	{
		door->state = D_CHANGE;
		// render open and close door;
		door->state = D_CLOSE;
	}
}
