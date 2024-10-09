/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:31:27 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 13:24:23 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define SCREEN_WIDTH 2048 // 1920
# define SCREEN_HEIGHT 1280 // 1080

# define RAY_ANGLE_DELTA 1
# define FIELD_OF_VIEW	64
# define NUM_RAYS (FIELD_OF_VIEW / RAY_ANGLE_DELTA)

# include "degree.h"

# ifndef CUBE_H
#  include "cube.h"
# endif

typedef enum e_error	t_error;
typedef struct s_data	t_data;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_cast_config
{
	t_point	pos;
	t_point dir;
	t_point	plane;
}	t_cast_config;

typedef struct s_ray
{
	double			camera_x;
	t_point			dir;
	t_point			side_dist;
	t_point			delta_dist;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			distance;
	double			height;
	t_image_index	index;
}	t_ray;

// Frame functions
t_error	build_frame(t_data *data);

// Ray casting functions
t_error	ray_casting(t_data *data, t_cast_config *cast, t_ray *rays);

// Point functions
t_point	create_point(double x, double y);

#endif
