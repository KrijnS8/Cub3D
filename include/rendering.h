/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:31:27 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/01 13:20:33 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define RAY_ANGLE_DELTA 10
# define FIELD_OF_VIEW	90
# define NUM_RAYS (FIELD_OF_VIEW / RAY_ANGLE_DELTA)

typedef enum e_error	t_error;
typedef struct s_data	t_data;

typedef struct s_line
{
	t_degree	degree;
	int			height;
	double		end_point;
}	t_line;

typedef struct s_ray
{
	double	vortex;
	double	end_point;
	t_line	line;
}	t_ray;

typedef struct s_frame
{
	void	*image;
	t_ray	rays[FIELD_OF_VIEW / RAY_ANGLE_DELTA];
}	t_frame;

// Frame functions
t_error	build_frame(t_data *data);

// Ray casting functions
t_error cast_ray(t_data *data, t_ray *ray);

#endif
