/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameplay.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 15:40:27 by splattje      #+#    #+#                 */
/*   Updated: 2024/11/04 11:39:39 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include <stddef.h>

# define PLAYER_SPEED 0.04
# define CAMERA_SPEED 0.7

# define WALL_COLLISION_OFFSET 0.1

typedef struct s_data	t_data;
typedef struct s_dpoint	t_dpoint;
typedef struct s_door	t_door;
typedef struct s_player	t_player;

int		handle_keypress(int keysym, t_data *data);
int		des_func(t_data *data);
int		handle_release(int keysym, t_data *data);
size_t	get_time(void);
void	do_movement(t_data *data);
void	open_close_door(t_player player, t_door *door, t_dpoint dir);

#endif
