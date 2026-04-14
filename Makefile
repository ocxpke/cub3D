# color bolds         #
B_BLACK = \033[1;30m
B_RED = \033[1;31m
B_GREEN = \033[1;32m
B_YELLOW = \033[1;33m
B_BLUE = \033[1;34m
B_MAGENTA = \033[1;35m
B_CYAN = \033[1;36m
B_WHITE = \033[1;37m

BOLD_BLACK   := $(shell tput bold; tput setaf 0)
BOLD_RED     := $(shell tput bold; tput setaf 1)
BOLD_GREEN   := $(shell tput bold; tput setaf 2)
BOLD_YELLOW  := $(shell tput bold; tput setaf 3)
BOLD_BLUE    := $(shell tput bold; tput setaf 4)
BOLD_MAGENTA := $(shell tput bold; tput setaf 5)
BOLD_CYAN    := $(shell tput bold; tput setaf 6)
BOLD_WHITE   := $(shell tput bold; tput setaf 7)
RESET        := $(shell tput sgr0)

LIBFT_PATH	= ./Libft
LIBFT		= $(LIBFT_PATH)/libft.a

#MINILIBX_PATH	= ./minilibx-linux
MINILIBX	= $(MINILIBX_PATH)/libmlx_Linux.a

SOURCES_FILES	= main.c \
				./parsing/parsing.c \
				./parsing/file_validation_utils.c \
				./parsing/split_file.c \
				./parsing/print_mapfile.c \
				./parsing/struct_init.c \
				./parsing/file_checklist.c \
				./parsing/map_placement.c \
				./parsing/elements_placement.c \
				./parsing/get_and_validate_elements.c \
				./parsing/get_tex_and_f_c.c \
				./parsing/find_map.c \
				./parsing/valid_textures.c \
				./parsing/valid_f_c.c \
				./parsing/get_color_val.c \
				./parsing/check_rgb.c \
				./parsing/valid_map.c \
				./parsing/valid_content.c \
				./parsing/valid_structure.c \
				./parsing/check_inner_chars.c \
				./parsing/free_all.c \
				./parsing/open_and_check_textures.c \
				./parsing/get_map_info.c \
				./parsing/map_info_utils.c \
				./parsing/check_for_anything_else.c

SOURCES_DIR	= ./source
INCLUDE		= cub3d.h

SOURCES		= $(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))
OBJECTS		= $(SOURCES:$(SOURCES_DIR)/%.c=$(SOURCES_DIR)/%.o)

NAME		= cub3d

CC		= cc
RM		= rm -f

CFLAGS		=  -g -Wall -Wextra -Werror -I$(SOURCES_DIR)
MLXFLAGS	= -L. -lXext -L. -lX11 -lm

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)
	@echo "${BOLD_CYAN}Done!${RESET}"
	@echo "${BOLD_GREEN}$(NAME) has been compiled successfully!${RESET}"

#$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $(NAME)
#	@echo '$(NAME) compiled successfully!'

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

#$(MINILIBX):
#	$(MAKE) -C $(MINILIBX_PATH)


$(SOURCES_DIR)/%.o: $(SOURCES_DIR)/%.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
#	$(MAKE) -C $(MINILIBX_PATH) clean
	$(RM) $(OBJECTS)
	@echo "$(OBJECTS) deleted!${RESET}"
	@echo "${BOLD_RED}$(NAME) deleted!${RESET}"
	@echo "${BOLD_CYAN}Done!${RESET}"

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	@echo "${BOLD_CYAN}Done!${RESET}"

re: fclean all

.PHONY: all clean fclean re