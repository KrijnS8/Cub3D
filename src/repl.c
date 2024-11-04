/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   repl.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:28:42 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/11/04 11:35:35 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "rendering.h"
#include "my_error.h"
#include "gameplay.h"
#include "degree.h"
#include <sys/time.h>

static void	frame_counter(void)
{
	static int				frames;
	static struct timeval	last_tv;
	struct timeval			tv;

	frames++;
	gettimeofday(&tv, NULL);
	if (tv.tv_usec - last_tv.tv_usec >= 1000000 || \
			tv.tv_sec - last_tv.tv_sec > 0)
	{
		ft_putnbr_fd(frames, 1);
		ft_putchar_fd('\n', 1);
		last_tv = tv;
		frames = 0;
	}
}

int	repl(t_data *data)
{
	int				x;
	int				y;
	double			angle_change;
	const int		screen_quarter = SCREEN_WIDTH / 4;

	frame_counter();
	data->map->player.p_angle = degree_add(
			double_to_degree(data->map->player.looking),
			data->map->player.p_angle);
	do_movement(data);
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (x < screen_quarter)
		angle_change = -1;
	else if (x > screen_quarter * 3)
		angle_change = 1;
	else
		angle_change = 0;
	data->map->player.p_angle = degree_add(
			double_to_degree(angle_change), data->map->player.p_angle);
	data->map->player.p_angle = \
		degree_add(double_to_degree(data->map->player.looking), \
									data->map->player.p_angle);
	build_frame(data);
	return (ERR_OK);
}
