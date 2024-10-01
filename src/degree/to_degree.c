/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_degree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:21:03 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/01 13:09:22 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "degree.h"
#include "../libft/libft.h"

#include <math.h>

t_degree	int_to_degree(int i)
{
	t_degree result;

	if (i < 0)
		i = (360 - (-i % 360));
	result.value = (double)(i % 360);
	return (result);
}

t_degree	double_to_degree(double d)
{
	t_degree result;

	result.value = fmod(d, 360.0);
	return (result);
}

