/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:55:20 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:50:19 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
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
