/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:01:04 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 10:32:54 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_error.h"
#include "cube.h"

static void	map_order_print(void)
{
	ft_putstr_fd("The map needs to have at least the following info in ", 2);
	ft_putstr_fd("this order\n", 2);
	ft_putstr_fd("NO image/FILENAME.xpm\n", 2);
	ft_putstr_fd("SO image/FILENAME.xpm\n", 2);
	ft_putstr_fd("WE image/FILENAME.xpm\n", 2);
	ft_putstr_fd("EA image/FILENAME.xpm\n\n", 2);
	ft_putstr_fd("F RGB_COLOR_VALUES\n", 2);
	ft_putstr_fd("C RGB_COLOR_VALUES\n\n", 2);
	ft_putstr_fd("THE MAP ITSELF\n", 2);
}

void	print_error(t_error error)
{
	if (error == ERR_MALLOC)
		perror("Error\nMalloc failed\n");
	else if (error == ERR_MAP_ORDER)
		map_order_print();
	else if (error == ERR_RGB)
		ft_putstr_fd("Error\nThe map only wants RGB\n", 2);
	else if (error == ERR_RGB_BOUND)
		ft_putstr_fd("Error\nRGB, value too heigh or too low\n", 2);
	else if (error == ERR_PLAYER)
		ft_putstr_fd("Error\nNone or too many players in map detected\n", 2);
	else if (error == ERR_FLOOR)
		ft_putstr_fd("Error\nThe map is not enclosed\n", 2);
	else if (error == ERR_EXTENTION)
		ft_putstr_fd("Error\nWrong extentrion\n", 2);
	else if (error == ERR_OPEN)
		perror("Error\nCan't open file\n");
	else if (error == ERR_MLX)
		ft_putstr_fd("Error\nMLX returned NULL\n", 2);
	else if (error == ERR_DOOR)
	{
		ft_putstr_fd("Error\nDoor needs two sides to be a wall and 2 ", 2);
		ft_putstr_fd("sides to be open space", 2);
	}
	else if (error == ERR_MAP_BOUND)
		ft_putstr_fd("Error\nIndex for map is out of bounds\n", 2);
}
