/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:08:15 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:47:47 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_p_hex(long n, char s_case)
{
	int		count;
	char	*glyphs;

	count = 0;
	glyphs = "0123456789abcdef";
	if (s_case == 'X')
		glyphs = "0123456789ABCDEF";
	if (n < 0)
		return (ft_p_hex(-n, s_case));
	else if (n < 16)
		return (ft_p_char(glyphs[n]));
	else
	{
		count = ft_p_hex(n / 16, s_case);
		return (count + ft_p_hex(n % 16, s_case));
	}
}
