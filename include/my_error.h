/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:46:20 by kschelvi          #+#    #+#             */
/*   Updated: 2024/11/01 09:47:58 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_ERROR_H
# define MY_ERROR_H

typedef enum e_error
{
	ERR_OK = 0,
	ERR_MALLOC,
	ERR_MAP_ORDER,
	ERR_RGB,
	ERR_RGB_BOUND,
	ERR_PLAYER,
	ERR_FLOOR,
	ERR_EXTENTION,
	ERR_OPEN,
	ERR_MLX,
	ERR_DOOR,
	ERR_MAP_BOUND
}	t_error;

void	print_error(t_error error);

#endif
