/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 15:11:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/15 16:44:57 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"

void	add_line(t_data *data, t_ray ray, int i)
{
	static int line_width = -1;
	int			x;
	int			y;
	int			dx;
	int			dy;

	if (line_width == -1)
	{
		line_width = SCREEN_WIDTH / get_num_rays();
	}
	x = line_width * i;
	y = (SCREEN_HEIGHT - ray.height) / 2;
	dx = 0;
	dy = 0;
	while (dx < line_width)
	{
		while (dy < ray.height)
		{
			put_pixel_img(data->frame, x + dx, y + dy, 0xFFFFFF);
			dy++;
		}
		dx++;
	}
}

t_error	render_frame(t_data *data, t_ray *rays)
{
	int	i;

	clear_img(data->frame);
	i = 0;
	while (i < get_num_rays())
	{
		add_line(data, rays[i], i);
		i++;
	}
	
	return (ERR_OK);
}
