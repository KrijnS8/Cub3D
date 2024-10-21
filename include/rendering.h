/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:31:27 by kschelvi          #+#    #+#             */
/*   Updated: 2024/10/23 10:03:14 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define SCREEN_WIDTH 2048
# define SCREEN_HEIGHT 1280

# define RAY_ANGLE_DELTA 0.125
# define FIELD_OF_VIEW	64

# include "degree.h"

# ifndef CUBE_H
#  include "cube.h"
# endif

typedef enum e_error	t_error;
typedef struct s_data	t_data;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_ipoint;

typedef struct s_cast_config
{
	t_dpoint	pos;
	t_dpoint	dir;
	t_dpoint	plane;
}	t_cast_config;

typedef struct s_ray
{
	double			camera_x;
	t_dpoint		dir;
	t_dpoint		side_dist;
	t_dpoint		delta_dist;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			distance;
	double			height;
	double			wall_x;
	t_image_index	index;
}	t_ray;

// Frame functions
int				build_frame(t_data *data);
t_error			render_frame(t_data *data, t_ray *rays);

// Ray casting functions
int				get_num_rays(void);
void			setup_ray(t_cast_config *cast, t_ray *ray, int num);
t_error			ray_casting(t_data *data, t_cast_config *cast, t_ray *rays);

// Point functions
t_dpoint			create_point(double x, double y);

// Image functions
void			put_img_to_img(t_img dst, t_img src, int x, int y);
void			put_pixel_img(t_img img, int x, int y, int color);
unsigned int	get_pixel_img(t_img img, int x, int y);
t_img			scale_image(t_data *data, t_img img, int new_width, int new_height);
void			clear_img(t_img src);

#endif
