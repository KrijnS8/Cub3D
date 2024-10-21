/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:10:32 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/21 13:48:53 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void update_pixels(char *odata, char *udata, t_ipoint original_size, t_ipoint new_size)
{
    double  scale_factor_x;
    double  scale_factor_y;
    int     original_offset;
    int     upscaled_offset;
    t_ipoint    i;

    scale_factor_x = (double)original_size.x / new_size.x;
    scale_factor_y = (double)original_size.y / new_size.y;
    i.y = 0;
    while (i.y < new_size.y)
	{
        i.x = 0;
        while (i.x < new_size.x)
		{
            original_offset = ((int)(i.y * scale_factor_y) * original_size.x + \
                                (int)(i.x * scale_factor_x)) * 4;
            upscaled_offset = (i.y * new_size.x + i.x) * 4;
            udata[upscaled_offset] = odata[original_offset];
            udata[upscaled_offset + 1] = odata[original_offset + 1];
            udata[upscaled_offset + 2] = odata[original_offset + 2];
            udata[upscaled_offset + 3] = odata[original_offset + 3];
            i.x++;
        }
        i.y++;
    }
}

static char	*get_char_img_data(void *texture, int *bpp, int *sl, int *endian)
{
	char	*data;

	data = mlx_get_data_addr(texture, bpp, sl, endian);
	return (data);
}

t_img	scale_image(t_data *data, t_img img, int new_width, int new_height)
{
	t_img		n_img;
	char		*odata;
	char		*udata;
	t_ipoint	osize;
	t_ipoint	usize;

	n_img.img_ptr = mlx_new_image(data->mlx, new_width, new_height);
	if (n_img.img_ptr == NULL)
		return (n_img);
	odata = img.addr;
	udata = get_char_img_data(n_img.img_ptr, &n_img.bpp, &n_img.line_len, &n_img.endian);
	osize.x = img.w;
	osize.y = img.h;
	usize.x = new_width;
	usize.y = new_height;
	update_pixels(odata, udata, osize, usize);
	n_img.w = new_width;
	n_img.h = new_height;
	return (n_img);
}
