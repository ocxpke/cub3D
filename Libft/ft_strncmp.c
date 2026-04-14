/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:49:11 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:53:40 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	int			result;

	i = 0;
	result = 0;
	if (n == 0)
	{
		return (result);
	}
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			result = ((unsigned char)s1[i] - (unsigned char)s2[i]);
			return (result);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	int		n = 10;
	char	string1[12] = "bye bye bye";
	char	string2[12] = "bye bye buy";
	int		res1 = ft_strncmp(string1, string2, n);
	int     res2 = strncmp(string1, string2, n);

	printf("%i", res1);
	write(1, "\n", 1);
    printf("\n%i", res2);
}
*/
