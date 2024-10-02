/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:27:09 by splattje          #+#    #+#             */
/*   Updated: 2024/10/02 09:49:48 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "gameplay.h"
#include "rendering.h"

t_img	new_img(t_data* data)
{
	t_img	image;
	image.img_ptr = data->map->images[N_WALL];
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
		&(image.line_len), &image.endian);
	image.w = 254;
	image.h = 254;
	return (image);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr
		+ (y * img.line_len) + (x * img.bpp / 8))));
}

void	update_screen(t_data *data, t_ray ray)
{
	int	ray_number;
	int	x;
	int	y;
	int	next;
	t_img image;

	ray_number = -1;
	while (++ray_number < NUM_RAYS)
	{
		x = ray_number * (NUM_RAYS);
		y = -1;
		image = new_img(data);
		next = (ray_number + 1) * NUM_RAYS;
		while (++y < ray.line.height)
			while (x < next)
				put_pixel_img(image, x++, y, data->map->c_color_hex);
		while (++y < SCREEN_HEIGHT)
			while (x < next)
				put_pixel_img(image, x++, y, data->map->c_color_hex);
		mlx_put_image_to_window(data->mlx, data->win, image.img_ptr, 0, 0);
	}
}

static void	move_camera(t_degree degree, t_data *data)
{
	data->map->player.p_angle = degree_add(data->map->player.p_angle, degree);
	//printf("camera angle is %f\n", map->player.p_angle.value);
	update_screen(data);
}

static void	do_player_movement(t_data *data)
{
	update_screen(data);
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
		move_camera(int_to_degree(0), data);
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
