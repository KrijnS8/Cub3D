/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:27:09 by splattje          #+#    #+#             */
/*   Updated: 2024/10/15 14:24:05 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "gameplay.h"
#include "rendering.h"

static void	move_camera(int look_angle, t_data *data)
{
	data->map->player.looking = look_angle;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (des_func(data));
	else if (keysym == XK_Left || keysym == XK_Right)
	{
		if (keysym == XK_Left)
			move_camera(-1, data);
		if (keysym == XK_Right)
			move_camera(1, data);
	}
	else
	{
		if (keysym == XK_w)
			data->map->player.move_fb = -1;
		if (keysym == XK_s)
			data->map->player.move_fb = 1;
		if (keysym == XK_d)
			data->map->player.move_lr = 1;
		if (keysym == XK_a)
			data->map->player.move_lr = -1;
	}
	return (0);
}

int	handle_release(int keysym, t_data *data)
{
	if (keysym == XK_Left || keysym == XK_Right)
		move_camera(0, data);
	else
	{
		if (keysym == XK_w || keysym == XK_s)
			data->map->player.move_fb = 0;
		if (keysym == XK_d || keysym == XK_a)
			data->map->player.move_lr = 0;
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
