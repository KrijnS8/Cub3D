/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:31:27 by kschelvi          #+#    #+#             */
/*   Updated: 2024/10/09 09:21:45 by splattje         ###   ########.fr       */
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

typedef struct s_dda_config
{
	t_point	pos;
	double	distance;
	t_point	start;
	t_point	dir;
	int		step_x;
	int		step_y;
	t_point	side_dist;
	t_point	delta;
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

typedef struct s_frame
{
	void	*image;
	t_ray	rays[FIELD_OF_VIEW / RAY_ANGLE_DELTA];
}	t_frame;

// Frame functions
t_error	build_frame(t_data *data);

// Ray casting functions
t_error	cast_ray(t_data *data, t_ray *ray);

// Point functions
t_point	create_point(double x, double y);

#endif
