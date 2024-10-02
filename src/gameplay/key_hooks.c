/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:27:09 by splattje          #+#    #+#             */
/*   Updated: 2024/10/02 12:56:43 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "gameplay.h"
#include "rendering.h"

// void	put_pixel_img(t_img img, int x, int y, int color)
// {
// 	char	*dst;

// 	if (color == (int)0xFF000000)
// 		return ;
// 	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
// 	{
// 		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
// 		*(unsigned int *) dst = color;
// 	}
// }

// unsigned int	get_pixel_img(t_img img, int x, int y)
// {
// 	return (*(unsigned int *)((img.addr
// 			+ (y * img.line_len) + (x * img.bpp / 8))));
// }

static void	move_camera(t_degree degree, t_data *data)
{
	data->map->player.p_angle = degree_add(data->map->player.p_angle, degree);
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
			move_camera(int_to_degree(-1), data);
		if (keysym == XK_Right)
			move_camera(int_to_degree(1), data);
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
		do_player_movement(data);
	}
	return (0);
}

int	handle_release(int keysym, t_data *data)
{
	if (keysym == XK_Left || keysym == XK_Right)
		move_camera(int_to_degree(0), data);
	else
	{
		if (keysym == XK_w || keysym == XK_s)
			data->map->player.move_fb = 0;
		if (keysym == XK_d || keysym == XK_a)
			data->map->player.move_lr = 0;
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
