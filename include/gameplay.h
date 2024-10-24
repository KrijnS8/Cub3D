/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameplay.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 15:40:27 by splattje      #+#    #+#                 */
/*   Updated: 2024/10/24 16:23:20 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include <stddef.h>

# define PLAYER_SPEED 0.075

typedef struct s_data	t_data;

int		handle_keypress(int keysym, t_data *data);
int		des_func(t_data *data);
int		handle_release(int keysym, t_data *data);
size_t	get_time(void);
void	do_movement(t_data *data);

#endif