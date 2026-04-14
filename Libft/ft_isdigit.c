/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:37:56 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:31:46 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	int	result;

	result = 0;
	if (c)
	{
		if ((c <= '9') && (c >= '0'))
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

	test = 'e';
	resultado = ft_isdigit(test);
	printf("%i \n", resultado);
	return (0);
}
*/
