/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:50:22 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:31:24 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	int	result;

	result = 0;
	if (c)
	{
		if (((c <= 'Z') && (c >= 'A'))
			|| ((c >= 'a') && (c <= 'z')))
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
	}
	return (result);
}
/*
int	main(void)
{
	int		resultado;
	char	test;

	test = '2';
	resultado = ft_isalpha(test);
	printf("%i \n", resultado);
	return (0);
}
*/
