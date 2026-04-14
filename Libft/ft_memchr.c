/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:51:37 by romorale          #+#    #+#             */
/*   Updated: 2024/04/21 17:26:26 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*un_s;
	unsigned char	un_c;
	size_t			i;

	un_s = (unsigned char *) s;
	un_c = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (un_s[i] == un_c)
		{
			return ((void *) &un_s[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
    const char	string[] = "123450006789";
    const char	character = '0';
	char		*resultmine;
	char		*resultreal;

    resultmine = ft_memchr(string, character, 7);
    resultreal = memchr(string, character, 7);
    printf("%s \n", resultmine);
	printf("%s \n", resultreal);
	return (0);
}
*/
