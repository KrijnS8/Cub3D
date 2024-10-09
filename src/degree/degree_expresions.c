/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   degree_expresions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:10:02 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/09 15:30:23 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "degree.h"
#include <math.h>

/**
 * @return Returns the addition of d1 and d2
 */
t_degree	degree_add(t_degree d1, t_degree d2)
{
	t_degree	result;

	result.value = fmod(d1.value + d2.value, 360.0);
	return (result);
}

/**
 * @return Returns the subtraction of d1 and d2
 */
t_degree	degree_sub(t_degree d1, t_degree d2)
{
	t_degree	result;

	result.value = fmod(d1.value - d2.value + 360.0, 360.0);
	return (result);
}

/**
 * @return Returns the multiplication of d1 and d2
 */
t_degree	degree_multi(t_degree d1, t_degree d2)
{
	t_degree	result;

	result.value = fmod(d1.value * d2.value, 360.0);
	return (result);
}

/**
 * @return Returns the division of d1 and d2
 */
t_degree	degree_div(t_degree d1, t_degree d2)
{
	t_degree	result;

	if (d2.value == 0)
		return (int_to_degree(0));
	result.value = fmod(d1.value / d2.value + 360, 360.0);
	return (result);
}
