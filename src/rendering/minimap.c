/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 11:33:26 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/11/04 11:44:24 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @param data pointer to the main data struct (t_data)
 * @param block_size size of the wall blocks
 * @param offset offset to sides of the screen
 * @brief renders the player on the minimap
 */
static void	render_player_minimap(t_data *data, int block_size, int offset)
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
 * @brief returns the block size depending on the map width and height
 */
static int	get_block_size(t_data *data)
{
	if (data->width > data->height)
		return (SCREEN_WIDTH / 5 / data->width);
	return (SCREEN_HEIGHT / 5 / data->height);
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
	const int	block_size = get_block_size(data);
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
