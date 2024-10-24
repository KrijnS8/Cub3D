/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 16:23:06 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/24 15:29:08 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @var dst the current pixel data of the image
 * @param img the image we want to make the changes to (t_img)
 * @param x the x corinate within the image
 * @param y the y corinate withing the image
 * @param color the color we want the pixel to become
 * @brief sets the x y pixel of the image to the given color
 */
void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

/**
 * @param img img struct countaining image info
 * @param x the x position in the image
 * @param y the y position in the image
 * @return returns the current pixel form the image
 */
unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr
			+ (y * img.line_len) + (x * img.bpp / 8))));
}

/**
 * @param dst image struct to the destination
 * @param src image struct to the source
 * @param x x coordinate
 * @param y y coordinate
 * @brief copies src onto dst on the given coordinates
 */
void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

/**
 * @param src img struct containing image info
 * @brief fills image with black pixels
 */
void	clear_img(t_img src)
{
	int	y;
	int	x;

	y = 0;
	while (y < src.h)
	{
		x = 0;
		while (x < src.w)
		{
			put_pixel_img(src, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

/**
 * @param img img struct containing image info
 * @param pos point struct containing position
 * @param length length of the line
 * @param color color of the line
 * @brief sets a line of given length at the given position
 */
void	put_line_to_image(t_img img, t_ipoint pos, int length, int color)
{
	int		x;
	int		y;
	int		i;
	char	*dst;

	if (color == (int)0xFF000000 || length <= 0)
		return ;
	x = pos.x;
	y = pos.y;
	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	i = 0;
	while (i++ < length)
		*(unsigned int *)(dst + (i - 1) * (img.bpp / 8)) = color;
}
