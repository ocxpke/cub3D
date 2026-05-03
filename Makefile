NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

MAP	:= src/map/map_view.c

PLAYER := src/player/player_view.c \
			src/player/player_movement.c\
			src/player/player_rotation.c

MLX42_MNG := src/mlx42_management/hooks.c \
				src/mlx42_management/window_management.c \
				src/mlx42_management/load_frames.c

DRAW_UTILS := src/draw_utils/line_algorithym.c

RAYCASTING := src/raycasting/raycasting.c

TIME_MNG := src/time_mng/get_time.c

PARSEO := src/parsing/parsing.c \
				src/parsing/file_validation_utils.c \
				src/parsing/split_file.c \
				src/parsing/print_mapfile.c \
				src/parsing/struct_init.c \
				src/parsing/file_checklist.c \
				src/parsing/map_placement.c \
				src/parsing/elements_placement.c \
				src/parsing/get_and_validate_elements.c \
				src/parsing/get_tex_and_f_c.c \
				src/parsing/find_map.c \
				src/parsing/valid_textures.c \
				src/parsing/valid_f_c.c \
				src/parsing/get_color_val.c \
				src/parsing/check_rgb.c \
				src/parsing/valid_map.c \
				src/parsing/valid_content.c \
				src/parsing/valid_structure.c \
				src/parsing/check_inner_chars.c \
				src/parsing/free_all.c \
				src/parsing/open_and_check_textures.c \
				src/parsing/get_map_info.c \
				src/parsing/map_info_utils.c \
				src/parsing/check_for_anything_else.c\
				src/parsing/square_map.c

SRCS	= $(VIEWS) $(MLX42_MNG) $(DRAW_UTILS) $(RAYCASTING)\
			$(MAP) $(PLAYER) $(TIME_MNG) $(PARSEO)\
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
	XDG_SESSION_TYPE=x11 DISPLAY=:0 ./cub3d ./src/placeholder_textures/valid_simple_map_cat_textures.cub

valgrind_run: all
	valgrind -s ./cub3d

.PHONY: all clean fclean re libmlx run valgrind_run
