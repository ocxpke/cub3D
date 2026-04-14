/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_digit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:25:27 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:47:29 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_p_digit(long n)
{
	int		count;
	char	*glyphs;

	count = 0;
	glyphs = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_p_digit(-n) + 1);
	}
	else if (n < 10)
	{
		return (ft_p_char(glyphs[n]));
	}
	else
	{
		count = ft_p_digit(n / 10);
		return (count + ft_p_digit(n % 10));
	}
}
