/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:10:37 by splattje          #+#    #+#             */
/*   Updated: 2024/10/02 13:12:20 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "rendering.h"
#include "my_error.h"
#include "gameplay.h"
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_putendl_fd("Error\n Not enough argumants", 2), 1);
	data = init_data();
	if (data == NULL)
		return (1);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (perror("Error\nMLX failed\n"), free_data(data), 1);
	if (!parse_input(argv[1], &data))
		return (ft_putendl_fd("parsing error", 2), free_data(data), 1);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cube");
	if (data->win == NULL)
		return (perror("Error\nMXL Window failed\n"), free_data(data), 1);
	build_frame(data);
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_hook(data->win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &handle_release, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &des_func, data);
	mlx_loop(data->mlx);
	mlx_do_key_autorepeaton(data->mlx);
	free_data(data);
}
