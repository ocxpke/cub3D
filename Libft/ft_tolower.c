/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:25:29 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:51:41 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int ch)
{
	if (ch)
	{
		if ((ch <= 'Z') && (ch >= 'A'))
		{
			ch = ch + 32;
		}
	}
	return (ch);
}
/*
int	main(void)
{
	char	test;
	char	resultado;

	test = 'A';
	resultado = ft_tolower(test);
	printf("%c \n", resultado);
	return (0);
}
*/
