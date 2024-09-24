/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   degree_expresions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:10:02 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/09/24 16:32:18 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "degree.h"
#include <math.h>

t_degree	degree_add(t_degree d1, t_degree d2)
{
	t_degree result;
	
    result.value = fmod(d1.value + d2.value, 360.0);
    return result;
}

t_degree	degree_sub(t_degree d1, t_degree d2)
{
	t_degree result;
	
    result.value = fmod(d1.value - d2.value + 360.0, 360.0);
    return result;
}

t_degree	degree_multi(t_degree d1, t_degree d2)
{
	t_degree result;
	
    result.value = fmod(d1.value * d2.value, 360.0);
    return result;
}

t_degree	degree_div(t_degree d1, t_degree d2)
{
	t_degree result;
	
    result.value = fmod(d1.value / d2.value + 360, 360.0);
    return result;
}
