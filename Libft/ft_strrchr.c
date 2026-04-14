/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:42 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:52:54 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			return (&((char *)s)[i]);
		}
		i--;
	}
	return (NULL);
}
/*
int main(void)
{
    char    str[30] = "abcedfghijklmnopqrstduvwxyz";
    char    *result = ft_strrchr(str, 'd');

    printf("\n%s", result);
    return (0);
}
*/
