/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:27:09 by splattje          #+#    #+#             */
/*   Updated: 2024/09/30 13:57:08 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "gameplay.h"

static void	move_camera(t_degree degree, t_map *map)
{
	map->player.p_angle = degree_add(map->player.p_angle, degree);
	printf("camera angle is %f\n", map->player.p_angle.value);
}

static void	do_player_movement(t_data *data)
{
	(void)data;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (des_func(data));
	else if (keysym == XK_Left || keysym == XK_Right)
	{
		if (keysym == XK_Left)
			move_camera(int_to_degree(-1), data->map);
		if (keysym == XK_Right)
			move_camera(int_to_degree(1), data->map);
	}
	else
	{
		if (keysym == XK_w)
			data->map->player.move_fb += -30;
		if (keysym == XK_s)
			data->map->player.move_fb += 30;
		if (keysym == XK_d)
			data->map->player.move_lr += 30;
		if (keysym == XK_a)
			data->map->player.move_lr += -30;
		do_player_movement(data);
	}
	return (0);
}

int	handle_release(int keysym, t_data *data)
{
	if (keysym == XK_Left || keysym == XK_Right)
		move_camera(int_to_degree(0), data->map);
	else
	{
		if (keysym == XK_w)
			data->map->player.move_fb -= -30;
		if (keysym == XK_s)
			data->map->player.move_fb -= 30;
		if (keysym == XK_d)
			data->map->player.move_lr -= 30;
		if (keysym == XK_a)
			data->map->player.move_lr -= -30;
		do_player_movement(data);
	}
	return (0);
}

int	des_func(t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx);
	free_data(data);
	exit(0);
	return (0);
}
