/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 15:27:09 by splattje      #+#    #+#                 */
/*   Updated: 2024/10/28 14:21:49 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "gameplay.h"
#include "rendering.h"
#include <math.h>

void	door_status_change(t_data *data, double start_x, double start_y,
	t_door *door)
{
	double	dx;
	double	dy;

	dx = cos(degree_to_radian(data->map->player.p_angle))
		* -data->map->player.move_fb * 0.25;
	dy = sin(degree_to_radian(data->map->player.p_angle))
		* -data->map->player.move_fb * 0.25;
	while (door != NULL)
	{
		while (start_y < 1.6)
		{
			while (start_x < 1.6)
			{
				if ((int)(data->map->player.p_y
					+ dy + start_y) == door->y
					&& (int)(data->map->player.p_x
					+ dx + start_x) == door->x)
					return (open_close_door(data, door));
				start_x += 0.1;
			}
			start_y += 0.1;
		}
		door = door->next;
	}
}

/**
 * @param data poiner to the main data struct (t_data)
 * @brief sets the movement based on the angle that we are looking at and
 * the keys that are pressed
 */
void	do_movement(t_data *data)
{
	double	dx;
	double	dy;
	t_door	*doors;

	dx = 0;
	dy = 0;
	do_dirctional_calculations(data, &dx, &dy);
	if (data->map->map[(int)(data->map->player.p_y + dy + 0.5)]
		[(int)(data->map->player.p_x + dx + 0.5)] != '1')
	{
		doors = door_exists(data, (int)(data->map->player.p_x + dx + 0.5),
				(int)(data->map->player.p_y + dy + 0.5));
		move(doors, data, dx, dy);
	}
}

/**
 * @param keysym the specific key thats pressed
 * @param data pointer to the main data struct
 * @return returns 0 when done
 * @brief checks which key is pressed and make sure de right values are stored
 */
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (des_func(data));
	else if (keysym == XK_Left || keysym == XK_Right)
	{
		if (keysym == XK_Left)
			data->map->player.looking = -CAMERA_SPEED;
		if (keysym == XK_Right)
			data->map->player.looking = CAMERA_SPEED;
	}
	else if (keysym == XK_e)
		door_status_change(data, -0.5, -0.5, data->map->doors);
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

/**
 * @param keysym the specific key being released
 * @param data pointer to the main data struct
 * @return returns 0 when done
 * @brief checks when keys are released and set the values back to zero
 */
int	handle_release(int keysym, t_data *data)
{
	if (keysym == XK_Left || keysym == XK_Right)
		data->map->player.looking = 0;
	else
	{
		if (keysym == XK_w || keysym == XK_s)
			data->map->player.move_fb = 0;
		if (keysym == XK_d || keysym == XK_a)
			data->map->player.move_lr = 0;
	}
	return (0);
}

/**
 * @param data pointer to the main data struct
 * @return returnes 0 when done
 * @brief when destroy event is called reanbles key_autorepeats,
 * cleans everything up, and exits program
 */
int	des_func(t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx);
	free_data(data);
	exit(0);
	return (0);
}
