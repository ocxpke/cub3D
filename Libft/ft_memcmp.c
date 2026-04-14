/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:35:29 by romorale          #+#    #+#             */
/*   Updated: 2024/04/21 18:36:20 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;
	int				result;

	i = 0;
	result = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
	{
		return (result);
	}
	while (i < n)
	{
		if ((unsigned char) str1[i] != (unsigned char) str2[i])
		{
			result = ((unsigned char) str1[i] - (unsigned char) str2[i]);
			return (result);
		}
		i++;
	}
	return (result);
}
/*
int main(void)
{
    int     n = 10;
    char    string1[12] = "bye bye bye";
    char    string2[12] = "bye bye buy";
    int     res1 = ft_memcmp(string1, string2, n);
    int     res2 = memcmp(string1, string2, n);

    printf("%i", res1);
    write(1, "\n", 1);
    printf("\n%i", res2);
}
*/
