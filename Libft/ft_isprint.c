/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:23:29 by romorale          #+#    #+#             */
/*   Updated: 2024/05/13 11:33:18 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	int	result;

	result = 0;
	if (c)
	{
		if ((c <= '~') && (c >= ' '))
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

	test = 'i';
	resultado = ft_isprint(test);
	printf("%i \n", resultado);
	return (0);
}
*/
