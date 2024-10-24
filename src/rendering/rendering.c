/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 15:11:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/24 16:46:04 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "my_error.h"
#include <math.h>

/**
 * @return line width calculated by screen width and number of rays
 */
static int	get_line_width(void)
{
	static int	line_width = -1;

	if (line_width == -1)
		line_width = SCREEN_WIDTH / get_num_rays();
	return (line_width);
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param rays pointer to an array of ray structs (t_ray)
 * @param i index of current ray in rays array
 * @param location_rays location of the current rays in original rays array
 * @brief renders a single ray
 */
static void	render_ray(t_data *data, t_ray *rays, int i)
{
	t_ipoint	pos;
	t_ipoint	src;
	const int	line_start = (SCREEN_HEIGHT - rays[i].height) / 2;
	const int	line_width = get_line_width();

	pos.x = line_width * i;
	pos.y = 0;
	while (pos.y < SCREEN_HEIGHT)
	{
		if (pos.y < line_start)
			put_line_to_image(data->frame, pos, \
								line_width, data->map->c_color_hex);
		else if (pos.y > line_start + rays[i].height - 1)
			put_line_to_image(data->frame, pos, \
								line_width, data->map->f_color_hex);
		else
		{
			src.x = rays[i].wall_x * data->map->img[rays[i].index].w;
			src.y = (int)(pos.y - line_start) *\
				(double)data->map->img[rays[i].index].h / rays[i].height;
			put_line_to_image(data->frame, pos, line_width, \
				get_pixel_img(data->map->img[rays[i].index], src.x, src.y));
		}
		pos.y++;
	}
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param block_size size of the wall blocks
 * @param offset offset to sides of the screen
 * @brief renders the player on the minimap
 */
void	render_player_minimap(t_data *data, int block_size, int offset)
{
	int	player_size;
	int	player_x;
	int	player_y;
	int	i;

	player_size = block_size * 3 / 4;
	player_x = (data->map->player.p_x + 0.25) * block_size + offset;
	player_y = (data->map->player.p_y + 0.25) * block_size + offset;
	i = 0;
	while (i < player_size)
	{
		put_line_to_image(data->frame, create_ipoint(player_x, player_y + i), \
							player_size, 0xdc143c);
		i++;
	}
}

/**
 * @param data pointer to the main data struct (t_data)
 * @brief renders the minimap on the frame
 */
void	render_minimap(t_data *data)
{
	int			x;
	int			y;
	int			i;
	const int	block_size = 15;
	const int	offset = 40;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->map->map[y][x] == '1')
			{
				i = 0;
				while (i++ < block_size)
					put_line_to_image(data->frame, \
						create_ipoint(x * block_size + offset, y * \
							block_size + i - 1 + offset), block_size, 0xccffff);
			}
			x++;
		}
		y++;
	}
	render_player_minimap(data, block_size, offset);
}

/**
 * @param data pointer to the main data struct (t_data)
 * @param rays pointer to an array of ray structs (t_ray)
 * @brief renders a single frame using the information from the rays array
 * @return an error code, rendered frame is stored in data struct
 */
t_error	render_frame(t_data *data, t_ray *rays)
{
	int			i;

	i = 0;
	while (i < get_num_rays())
	{
		render_ray(data, rays, i);
		i++;
	}
	render_minimap(data);
	return (ERR_OK);
}
