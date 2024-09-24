/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:10:37 by splattje          #+#    #+#             */
/*   Updated: 2024/08/22 12:06:04 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_putendl_fd("Error\n Not enough argumants", 2), 1);
	data = init_data();
	if (data == NULL)
		return (1);
	if (!parse_input(argv[1], &data))
		return (ft_putendl_fd("parsing error", 2), free_data(data), 1);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (perror("Error\nMLX failed\n"), free_data(data), 1);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cube");
	if (data->win == NULL)
		return (perror("Error\nMXL Window failed\n"), free_data(data), 1);
	free_data(data);
}
