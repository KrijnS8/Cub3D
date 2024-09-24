/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_to_degree.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 15:59:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/09/24 16:38:04 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "degree.h"

t_degree	char_to_degree(char c)
{
	if (c == 'N' || c == 'n')
		return (int_to_degree(0));
	if (c == 'S' || c == 's')
		return (int_to_degree(180));
	if (c == 'W' || c == 'w')
		return (int_to_degree(270));
	if (c == 'E' || c == 'e')
		return (int_to_degree(90));
	return (int_to_degree(0));
}
