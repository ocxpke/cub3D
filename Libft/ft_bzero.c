/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:22:33 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:35:25 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp_s;

	temp_s = (char *)s;
	while (n > 0)
	{
		*(temp_s++) = 0;
		n--;
	}
}
/*
int main(void)
{
    char    str[30] = "abcdefghijklmnopqrstuvwxyz";

    printf("\nBefore: %s\n", str);
	//bzero(str + 6, 10);
    ft_bzero(str + 6, 10);
    printf("\nAfter: %s\n", str);
    return (0);
}
*/
