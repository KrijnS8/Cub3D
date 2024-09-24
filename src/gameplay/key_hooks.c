/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:27:09 by splattje          #+#    #+#             */
/*   Updated: 2024/09/24 17:21:06 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <sys/time.h>

static void move_camera(t_degree degree, bool flag, t_map *map)
{
	static bool check;

	check = flag;
	while(flag)
	{
		map->player.p_angle = degree_add(map->player.p_angle, degree);
		printf("degree is %f\n", map->player.p_angle.value);
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	t_degree	degree;

	if (keysym == XK_Escape)
	{
		free_data(data);
		exit(0);
	}
	if (keysym == XK_Left || keysym == XK_Right)
	{
		if (keysym == XK_Left)
			degree = int_to_degree(1);
		if (keysym == XK_Right)
			degree = int_to_degree(-1);
		move_camera(degree, true, data->map);
	}
	if (keysym == XK_w)
		data->map->player.move_fb += 30;
	if (keysym == XK_s)
		data->map->player.move_fb += -30;
	if (keysym == XK_d)
		data->map->player.move_lr += 30;
	if (keysym == XK_a)
		data->map->player.move_lr += -30;
	return (0);
}

int handle_release(int keysym, t_data *data)
{
	t_degree	degree;

	(void)data;
	if (keysym == XK_Left || keysym == XK_Right)
	{
		degree = int_to_degree(0);
		move_camera(degree, false, data->map);
	}
	if (keysym == XK_w)
		data->map->player.move_fb -= 30;
	if (keysym == XK_s)
		data->map->player.move_fb -= -30;
	if (keysym == XK_d)
		data->map->player.move_lr -= 30;
	if (keysym == XK_a)
		data->map->player.move_lr -= -30;
	return (0);
}

int	destroy_hook_function(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}
