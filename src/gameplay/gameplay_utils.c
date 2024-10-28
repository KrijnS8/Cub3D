/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:32:14 by splattje          #+#    #+#             */
/*   Updated: 2024/10/28 16:18:14 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "gameplay.h"
#include "rendering.h"
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

void	open_close_door(t_player player, t_door *door, t_dpoint dir)
{
	t_dpoint	range;

	if (door->state == D_CLOSE)
		door->state = D_OPEN;
	else if (door->state == D_OPEN)
	{
		range.y = -0.2;
		while (range.y < 0.3)
		{
			range.x = -0.2;
			while (range.x < 0.3)
			{
				if ((int)(player.p_y + dir.y + range.y) != door->y
					|| (int)(player.p_x + dir.x + range.x) != door->x)
					door->state = D_CLOSE;
				else
				{
					door->state = D_OPEN;
					return ;
				}
				range.x += 0.1;
			}
			range.y += 0.1;
		}
	}
}
