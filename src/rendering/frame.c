/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frame.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:43:45 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/01 14:57:16 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"

#include "cube.h"

void	init_rays(t_ray *rays, double p_angle)
{
	size_t		i;
	t_degree	last_angle;

	i = 0;
	while (i < NUM_RAYS)
	{
		if (i == 0)
		{
			rays[i].degree = double_to_degree(p_angle - FIELD_OF_VIEW / 2);
			last_angle = rays[i].degree;
			rays[i].line.num = i;
			i++;
			continue;
		}
		last_angle = degree_add(last_angle, int_to_degree(RAY_ANGLE_DELTA));
		rays[i].degree = last_angle;
		rays[i].line.num = i;
		i++;
	}
}

t_error	build_frame(t_data *data)
{
	void	*frame;
	t_ray	rays[NUM_RAYS];

	frame = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	init_rays(rays, data->map->player.p_angle.value);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		printf("%f\n", rays[i].degree.value);
		cast_ray(data, &(rays[i]));
	}
	return (ERR_OK);
}
