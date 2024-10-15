/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_degree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:21:03 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/15 13:13:36 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "degree.h"
#include "../libft/libft.h"

#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/**
 * @param i an integer value representing the angle in degrees
 * @return A degree struct containing the converted angle value
 */
t_degree	int_to_degree(int i)
{
	t_degree	result;

	if (i < 0)
		i = (360 - (-i % 360));
	result.value = (double)(i % 360);
	return (result);
}

/**
 * @param d a double value representing the angle in degrees
 * @return A degree struct containing the converted angle value
 */
t_degree	double_to_degree(double d)
{
	t_degree	result;

	if (d < 0)
		d = (360 - fmod(-d, 360));
	result.value = fmod(d, 360.0);
	return (result);
}

/**
 * @param d a degree struct representing the angle in degrees
 * @return A double value containing the equivalent angle in radians
 */
double	degree_to_radian(t_degree d)
{
	double	radian;

	radian = (d.value - 90.0) * (M_PI / 180.0);
	return (radian);
}
