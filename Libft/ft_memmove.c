/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:28:07 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:49:05 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*temp_dst;
	char	*temp_src;

	if (!src && !dst)
		return (NULL);
	temp_dst = (char *)dst;
	temp_src = (char *)src;
	i = 0;
	if (temp_dst < temp_src)
	{
		while (i < n)
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	else
	{
		while (n--)
		{
			temp_dst[n] = temp_src[n];
		}
	}
	return (dst);
}
/*
int main(void)
{
    char    string1[] = "123456789";
    char    string2[] = "000";

    printf("%s \n", string2);
    //ft_memmove(string2, string1, 4);
    memmove(string2, string1, 4);
    printf("%s \n", string2);
}
*/
