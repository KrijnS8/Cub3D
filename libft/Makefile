NAME = libft.a

SOURCES_MAND = ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_iswhitespace.c \
			ft_atol.c \
			ft_output.c \
			ft_printf.c \
			ft_ptr_to_hex.c \
			ft_uint_to_hex_uplow.c \
			ft_uitostr.c \
			ft_fprintf.c \
			ftf_output.c \
			ftf_ptr_to_hex.c \
			ftf_uint_to_hex_uplow.c \
			ftf_uitostr.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

GNL_DIR = ./Get_Next_Line

OBJ_DIR_MAND = ./obj_mand
OBJ_DIR_GNL = ./obj_gnl

DEP_MAND = $(OBJ_MAND:.o=.d)
DEP_GNL = $(OBJ_GNL:.o=.d)

GNL_SOURCES = $(GNL_DIR)/get_next_line.c \
			$(GNL_DIR)/get_next_line_utils.c \

OBJS_GNL = $(addprefix $(OBJ_DIR_GNL)/, $(GNL_SOURCES:.c=.o))

OBJS_MAND = $(addprefix $(OBJ_DIR_MAND)/, $(SOURCES_MAND:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3

AR = ar

all: $(NAME) gnl

$(NAME): $(OBJS_MAND) | $(OBJ_DIR_MAND)
	@$(AR) rcs $(NAME) $(OBJS_MAND)

gnl: $(OBJS_GNL) | $(OBJ_DIR_GNL)
	@$(AR) rcs $(NAME) $(OBJS_GNL)

$(OBJ_DIR_MAND)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_GNL)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP_MAND)
-include $(DEP_GNL)

clean:
	@rm -rf $(OBJ_DIR_MAND) $(OBJ_DIR_GNL)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re gnl