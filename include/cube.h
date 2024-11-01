/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:11:14 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 10:16:04 by splattje         ###   ########.fr       */
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

# include "degree.h"

# define IMAGE_WIDTH 256
# define IMAGE_HEIGHT 256

typedef enum e_error	t_error;

typedef enum e_image_index
{
	N_WALL = 0,
	S_WALL = 1,
	W_WALL = 2,
	E_WALL = 3,
	DOOR = 4
}	t_image_index;

typedef enum e_door_state
{
	D_CLOSE = 0,
	D_OPEN = 1,
	D_CHANGE = 2
}	t_door_state;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map_list
{
	char				*line;
	size_t				line_size;
	struct s_map_list	*next;
}	t_map_list;

typedef struct s_player
{
	double		p_x;
	double		p_y;
	char		p_face;
	t_degree	p_angle;
	int			move_fb;
	int			move_lr;
	double		looking;
}	t_player;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
	struct s_door	*next;
}	t_door;

typedef struct s_map
{
	t_map_list	*map_list;
	char		**map;
	char		*n_image_location;
	char		*s_image_location;
	char		*w_image_location;
	char		*e_image_location;
	char		*door_file_location;
	t_img		img[5];
	char		*c_color;
	char		*f_color;
	int			c_color_hex;
	int			f_color_hex;
	t_door		*doors;
	t_player	player;
}	t_map;

typedef struct s_data
{
	t_map	*map;
	int		height;
	int		width;
	void	*mlx;
	void	*win;
	t_img	frame;
}	t_data;

bool		parse_input(char *input, t_data **data);
void		free_map(t_map *map);
void		free_data(t_data *data);
t_data		*init_data(void);
t_map_list	*new_map_list(char *line);
size_t		map_list_size(t_map_list *list);
void		map_list_add_back(t_data **head, t_map_list *new);
char		*set_map_info(t_map_list *head, int skip);
void		free_2d_array(char **array);
void		get_map_height_width(t_data **data);
bool		check_map(t_map **map, t_data *data);
bool		set_images(t_data **data);
void		put_pixel_img(t_img img, int x, int y, int color);
bool		check_door(t_map **map, t_data *data, int x, int y);
t_door		*door_exists(t_data *data, int x, int y);
void		do_movement(t_data *data);
void		do_dirctional_calculations(t_data *data, double *dx, double *dy);
void		move(t_door *doors, t_data *data, double dx, double dy);
bool		check_door_file(t_map **map);
bool		check_door_floor(t_map **map, int x, int y, t_data *data);
bool		floor_fill(char **map, int y, int x, int height);
bool		check_postion(char **map, int y, int x);
int			set_map_object(t_map_list **map, char ***result, int index);
bool		set_wall_textures(t_map_list **map, char ***result, int index);
int			set_max(t_map_list *map);

t_degree	char_to_degree(char c);

int			repl(t_data *data);

#endif
