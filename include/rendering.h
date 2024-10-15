/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:31:27 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/15 14:54:31 by kschelvi      ########   odam.nl         */
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

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_cast_config
{
	t_point	pos;
	t_point	dir;
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
int	build_frame(t_data *data);

// Ray casting functions
int		get_num_rays(void);
void	setup_ray(t_cast_config *cast, t_ray *ray, int num);
t_error	ray_casting(t_data *data, t_cast_config *cast, t_ray *rays);

// Point functions
t_point	create_point(double x, double y);

#endif
