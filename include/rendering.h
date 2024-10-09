/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:31:27 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 12:37:44 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define SCREEN_WIDTH 2048 // 1920
# define SCREEN_HEIGHT 1280 // 1080

# define RAY_ANGLE_DELTA 1
# define FIELD_OF_VIEW	64
# define NUM_RAYS (FIELD_OF_VIEW / RAY_ANGLE_DELTA)
# define FIELD_OF_VIEW	90
# define NUM_RAYS (int)(FIELD_OF_VIEW / RAY_ANGLE_DELTA)

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
	double	camera_x;
	t_point	ray_dir;
	t_point	side_dist;
	t_point	delta_dist;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	double	distance;
	
}	t_dda_config;

typedef struct s_line
{
	int	num;
	int	height;
}	t_line;

typedef struct s_ray
{
	t_degree		degree;
	double			distance;
	t_line			line;
	t_image_index	index;
}	t_ray;

// Frame functions
t_error	build_frame(t_data *data);

// Ray casting functions
t_error	cast_ray(t_data *data, t_ray *ray);

// Point functions
t_point	create_point(double x, double y);

#endif
