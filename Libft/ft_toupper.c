/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:52:48 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:51:18 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int ch)
{
	if (ch)
	{
		if ((ch <= 'z') && (ch >= 'a'))
		{
			ch = ch - 32;
		}
	}
	return (ch);
}
/*
int	main(void)
{
	char	test;
	char	resultado;

	test = 'e';
	resultado = ft_toupper(test);
	printf("%c \n", resultado);
	return (0);
}
*/
