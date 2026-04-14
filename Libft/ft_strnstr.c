/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:25:33 by romorale          #+#    #+#             */
/*   Updated: 2024/04/25 13:39:55 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, int len)
{
	unsigned int	j;
	unsigned int	i;

	i = 0;
	if (to_find[0] == 0)
	{
		return ((char *) str);
	}
	while (str[i] && (i <= (unsigned int) len))
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i + j]
			&& i + j < (unsigned int) len)
		{
			j++;
			if (to_find[j] == 0)
			{
				return ((char *) &str[i]);
			}
		}
		i++;
	}
	return (0);
}
/*
int main(void)
{
    char    string1[] = "lorem ipsum dolor sit amet";
    char    string2[] = "dolor";

    printf("%s", ft_strnstr(string1, string2, 13));
	printf("\n%s", strnstr(string1, string2, 13));
    return (0);
}
*/
