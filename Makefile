NAME = cube3D

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP -g -I./include

MINILIBX_DIR = mlx
MINILIBX = $(MINILIBX_DIR)/libmlx.a
MLXFLAGS = -L $(MINILIBX_DIR) -lmlx -Ilmlx -lXext -lX11 -I$(MINILIBX_DIR)

MATHFLAGS = -lm

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJ_DIR = obj

vpath %.c $(SRC_DIR)

SRC = main.c \
		initializing.c \
		freeing.c \
		parsing.c \
		parsing_utils.c \
		map_checking.c \
		set_wall_images.c \
		repl.c \
		my_error.c \
		char_to_degree.c \
		degree/degree_expresions.c \
		degree/to_degree.c \
		rendering/frame.c \
		rendering/ray_casting.c \
		gameplay/key_hooks.c \
		char_to_degree.c
		

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) gnl

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	@$(CC) $(CFLAGS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $@ $^ $(MATHFLAGS)
	@echo Done compiling!

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	@rm -rf $(OBJ_DIR)
	@echo Deleted objects!

fclean: clean
	@rm -f $(NAME)
	@echo Deleted program!

re: fclean all

.PHONY: all clean fclean re clone