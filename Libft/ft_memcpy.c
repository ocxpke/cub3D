/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:46:58 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:45:30 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (dst == (void *)0 && src == (void *)0)
	{
		return (dst);
	}
	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	i = 0;
	while (n > 0)
	{
		(temp_dst)[i] = (temp_src)[i];
		n--;
		i++;
	}
	return (dst);
}
/*
int main(void)
{
    char    string1[] = "1111111111";
    char    string2[] = "2222222222";

    printf("%s \n", string2);
    ft_memcpy(string2, string1, 5);
	//memcpy(string2, string1, 5);
    printf("%s \n", string2);
}
*/
