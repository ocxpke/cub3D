/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:16:51 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:32:50 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	int	result;

	result = 0;
	if ((c <= 127) && (c >= 0))
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return (result);
}
/*
int	main(void)
{
	int		resultado;
	char	test;

	test = 'e';
	resultado = ft_isascii(test);
	printf("%i \n", resultado);
	return (0);
}
*/
