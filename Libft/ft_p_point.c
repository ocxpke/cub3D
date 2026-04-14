/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:13:04 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:48:00 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_p_point(size_t n, int flag)
{
	long	count;
	char	*glyphs;

	count = 0;
	glyphs = "0123456789abcdef";
	if (flag == 0 && n == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else if (flag == 0 && n != 0)
	{
		write(1, "0x", 2);
		return (count += ft_p_point(n, 1) + 2);
	}
	else
	{
		if (n < 16)
			return (ft_p_char(glyphs[n]));
		else
		{
			count += ft_p_point(n / 16, 1);
			return (count + ft_p_point(n % 16, 1));
		}
	}
}
