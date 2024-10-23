/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   repl.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:28:42 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/22 16:11:19 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "rendering.h"
#include "my_error.h"
#include "gameplay.h"
#include "degree.h"

int	repl(t_data *data)
{
	int				x;
	int				y;

	data->map->player.p_angle = degree_add(
			int_to_degree(data->map->player.looking),
			data->map->player.p_angle);
	do_movement(data);
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (x < (SCREEN_WIDTH / 4))
		data->map->player.p_angle = degree_add(
				int_to_degree(-1), data->map->player.p_angle);
	else if (x > (SCREEN_WIDTH / 4) * 3)
		data->map->player.p_angle = degree_add(
				int_to_degree(1), data->map->player.p_angle);
	else
		data->map->player.p_angle = degree_add(
				int_to_degree(0), data->map->player.p_angle);
	build_frame(data);
	data->map->player.p_angle = \
		degree_add(int_to_degree(data->map->player.looking), \
									data->map->player.p_angle);
	return (ERR_OK);
}
