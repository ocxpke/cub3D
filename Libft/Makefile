NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = 	ft_strlen.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strlcpy.c\
			ft_split.c ft_itoa.c ft_strchr.c get_next_line.c get_next_line_utils.c\
			ft_format.c ft_p_char.c ft_p_digit.c ft_p_hex.c ft_p_point.c\
			ft_p_str.c ft_printf.c\
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strncmp.c ft_strnstr.c ft_memchr.c ft_memcmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
		
OBJ = $(SOURCES:.c=.o)
RM = rm -f
AR = ar rcs

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

bonus:	$(NAME)
	$(AR) $(NAME)

clean:
	$(RM) $(OBJ)
	@echo "objects deleted"

fclean: clean
	$(RM) $(NAME)
	@echo "libft deleted"

re: fclean all

.PHONY: all clean fclean re
