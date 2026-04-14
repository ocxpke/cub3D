/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:55:20 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:53:36 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr_gnl(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&((char *)str)[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&((char *)str)[i]);
	return (NULL);
}

char	*ft_substr_gnl(const char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_str;

	i = 0;
	if (!str)
		return (NULL);
	if (start > ft_strlen(str))
	{
		sub_str = malloc(sizeof(char) * (1));
		if (!sub_str)
			return (NULL);
		sub_str[0] = '\0';
		return (sub_str);
	}
	if (ft_strlen(str) - start < len)
		len = ft_strlen(str) - start;
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (NULL);
	while (start < ft_strlen(str) && i < len && str[start])
		sub_str[i++] = str[start++];
	sub_str[i] = '\0';
	return (sub_str);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	char	*joint_str;
	size_t	i;
	size_t	j;

	if (!str1)
	{
		str1 = malloc(sizeof(char) + 1);
		if (!str1)
			return (NULL);
		str1[0] = 0;
	}
	joint_str = (char *)malloc(sizeof(char)
			* ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!joint_str)
		return (ft_free(&str1));
	i = -1;
	while (str1[++i])
		joint_str[i] = str1[i];
	j = -1;
	while (str2[++j])
		joint_str[i + j] = str2[j];
	joint_str[i + j] = '\0';
	free(str1);
	return (joint_str);
}
