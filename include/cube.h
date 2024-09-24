/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 10:11:14 by splattje      #+#    #+#                 */
/*   Updated: 2024/09/24 15:15:28 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/libft.h"
# include "../libft/Get_Next_Line/get_next_line.h"
# include "../mlx/mlx.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>

# define IMAGE_SIZE_X 11
# define IMAGE_SIZE_Y 11

enum e_image_index
{
	N_WALL = 0,
	S_WALL = 1,
	W_WALL = 2,
	E_WALL = 3
};

typedef struct s_map_list
{
	char				*line;
	size_t				line_size;
	struct s_map_list	*next;
}	t_map_list;

typedef struct s_map
{
	t_map_list	*map_list;
	char		**map;
	char		*n_image_location;
	char		*s_image_location;
	char		*w_image_location;
	char		*e_image_location;
	void		**images;
	char		*c_color;
	char		*f_color;
	int			c_color_hex;
	int			f_color_hex;
	int			p_x;
	int			p_y;
	char		p_face;
}	t_map;

typedef struct s_data
{
	t_map	*map;
	int		height;
	int		width;
	void	*mlx;
	void	*win;
}	t_data;

bool		parse_input(char *input, t_data **data);
void		free_map(t_map *map, void *mlx);
void		free_data(t_data *data);
t_data		*init_data(void);
t_map_list	*new_map_list(char *line);
size_t		map_list_size(t_map_list *list);
void		map_list_add_back(t_data **head, t_map_list *new);
char		*set_map_info(t_map_list *head, int skip);
void		free_2d_array(char **array);
void		get_map_height_width(t_data **data);
bool		check_map(t_map **map, int height);
int			set_wall_image(void *mlx, t_map *map);

#endif