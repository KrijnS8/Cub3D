/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_error.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:46:20 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/09/24 13:47:23 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_ERROR_H
# define MY_ERROR_H

typedef enum e_error
{
	ERR_OK = 0,
	ERR_MALLOC
}	t_error;

void	print_error();

#endif
