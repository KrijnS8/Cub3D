/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_degree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:21:03 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 14:13:03 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "degree.h"
#include "../libft/libft.h"

#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_degree	int_to_degree(int i)
{
	t_degree	result;

	if (i < 0)
		i = (360 - (-i % 360));
	result.value = (double)(i % 360);
	return (result);
}

t_degree	double_to_degree(double d)
{
	t_degree	result;

	if (d < 0)
		d = (360 - fmod(-d, 360));
	result.value = fmod(d, 360.0);
	return (result);
}

double	degree_to_radian(t_degree d)
{
	double	radian;

	radian = d.value * M_PI / 180.0;
	return (radian);
}
