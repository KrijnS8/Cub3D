/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_to_degree.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 15:59:48 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/09/24 16:02:08 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	char_to_degree(char c)
{
	if (c == 'N' || c == 'n')
		return (0);
	if (c == 'S' || c == 's')
		return (180);
	if (c == 'W' || c == 'w')
		return (270);
	if (c == "E" || c == 'e')
		return (90);
	return (-1);
}
