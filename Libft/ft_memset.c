/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:56:26 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:34:34 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp_s;

	temp_s = (unsigned char *)s;
	while (n > 0)
	{
		*(temp_s++) = (unsigned char )c;
		n--;
	}
	return (s);
}
/*
int	main(void)
{
	char	str[30] = "abcdefghijklmnopqrstuvwxyz";

	printf("\nBefore: %s\n", str);
	ft_memset(str + 6, '!', 10);
	printf("\nAfter: %s\n", str);
	return (0);
}
*/
