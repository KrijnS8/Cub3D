/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   degree.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:08:09 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/10/01 13:39:21 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEGREE_H
# define DEGREE_H

typedef struct s_degree
{
	double	value;
}	t_degree;

t_degree	degree_add(t_degree d1, t_degree d2);
t_degree	degree_sub(t_degree d1, t_degree d2);
t_degree	degree_multi(t_degree d1, t_degree d2);
t_degree	degree_div(t_degree d1, t_degree d2);

t_degree	int_to_degree(int i);
t_degree	double_to_degree(double d);

double		degree_to_radian(t_degree d);

#endif
