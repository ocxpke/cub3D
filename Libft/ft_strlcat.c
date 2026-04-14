/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:25:44 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:50:51 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dlen;
	unsigned int	slen;

	i = 0;
	j = 0;
	while (dest[j] != '\0')
	{
		j++;
	}
	dlen = j;
	slen = ft_strlen((char *)src);
	if (size == 0 || size <= dlen)
	{
		return (slen + size);
	}
	while (src[i] != '\0' && i < size - dlen - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dlen + slen);
}
/*
int	main(void)
{
	char	string1[] = " good bye.";
	char	string2[] = "i'm leaving,";

	printf("%s \n", string2);
	printf("%i \n", ft_strlcat(string2, string1, 30));
	printf("%s \n", string2);
}
*/
