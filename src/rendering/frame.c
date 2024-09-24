/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frame.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:43:45 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/09/24 16:44:12 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"

#include "cube.h"

void	init_rays(t_ray *rays, double p_angle)
{
	size_t	i;
	double	last_angle;

	i = 0;
	while (i < NUM_RAYS)
	{
		if (i == 0)
		{
			rays[i].vortex = p_angle - FIELD_OF_VIEW / 2;
			last_angle = rays[i].vortex;
			i++;
			continue;
		}
		last_angle += RAY_ANGLE_DELTA;
		rays[i].vortex = last_angle;
		i++;
	}
}

t_error	build_frame(t_data *data)
{
	void	*frame;
	t_ray	rays[NUM_RAYS];

	frame = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	init_rays(rays, data->map->player.p_face);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		ft_printf("test\n");
	}
	return (ERR_OK);
}
