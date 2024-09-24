/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:27 by splattje          #+#    #+#             */
/*   Updated: 2024/09/24 16:23:21 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

typedef struct s_data	t_data;

int	handle_keypress(int keysym, t_data *data);
int	destroy_hook_function(t_data *data);
int handle_release(int keysym, t_data *data);

#endif