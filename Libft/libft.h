/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:55:20 by romorale          #+#    #+#             */
/*   Updated: 2026/03/15 16:52:33 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  10
# endif

size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_substr(const char *str, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			**ft_split(char *s, char c);
char			*ft_strchr(const char *str, int c);
char			*get_next_line(int fd);
size_t			ft_strlen_gnl(const char *str);
char			*ft_strchr_gnl(const char *str, int c);
char			*ft_substr_gnl(const char *str, unsigned int start, size_t len);
char			*ft_strjoin_gnl(char *str1, char *str2);
char			*ft_free(char **str);
int				ft_printf(const char*format, ...);
int				ft_format(char specifier, va_list ap);
int				ft_p_digit(long n);
int				ft_p_str(char *s);
int				ft_p_char(long int c);
int				ft_p_hex(long n, char s_case);
int				ft_p_point(size_t n, int flag);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isdigit(int c);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *str, const char *to_find, int len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned int	ft_strlcat(char *dest, const char *sr, unsigned int size);
int				ft_tolower(int ch);
int				ft_toupper(int ch);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t num, size_t size);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

#endif
