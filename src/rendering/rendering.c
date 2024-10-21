/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 15:11:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/21 16:48:08 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include <math.h>

void	render_wall(t_data *data, t_ray *rays, int n)
{
	(void)data;
	int	i;

	i = 0;
	while (i < n)
	{
		printf("map_x: %d, map_y: %d\n", rays[i].map_x, rays[i].map_y);
		i++;
	}
}

t_error	render_frame(t_data *data, t_ray *rays)
{
	int			i;
	int			j;
	t_ipoint	wall;

	clear_img(data->frame);
	i = 0;
	while (i < get_num_rays())
	{
		j = 0;
		wall.x = rays[i].map_x;
		wall.y = rays[i].map_y;
		while (rays[i + j].map_x == wall.x && rays[i + j].map_y == wall.y)
			j++;
		render_wall(data, &(rays[i]), j);
		i += j;
	}
	return (ERR_OK);
}
