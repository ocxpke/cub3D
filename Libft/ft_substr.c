/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:55:20 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:53:00 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
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
