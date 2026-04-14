/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:57:25 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:32:13 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	result;

	result = 0;
	if (c)
	{
		if (((c <= '9') && (c >= '0'))
			|| ((c <= 'Z') && (c >= 'A'))
			|| ((c <= 'z') && (c >= 'a')))
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

	test = '?';
	resultado = ft_isalnum(test);
	printf("%i \n", resultado);
	return (0);
}
*/
