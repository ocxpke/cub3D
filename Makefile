NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

VIEWS	:= src/views/map_view.c \
			src/views/player_view.c

MLX42_MNG := src/mlx42_management/hooks.c \
				src/mlx42_management/window_management.c

DRAW_UTILS := src/draw_utils/line_algorithym.c

RAYCASTING := src/raycasting/raycasting.c

SRCS	= $(VIEWS) $(MLX42_MNG) $(DRAW_UTILS) $(RAYCASTING)\
			src/main.c

OBJ_DIR	:= build/objs

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	make -C $(LIBFT)

$(OBJS) : $(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[34mCompiling: \033[0m$<\n"

$(NAME): $(OBJS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	make clean -C $(LIBFT)
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	make fclean -C $(LIBFT)
	@rm -rf $(NAME)

re: clean all

run: all
	XDG_SESSION_TYPE=x11 DISPLAY=:0 ./cub3d

.PHONY: all clean fclean re libmlx run
