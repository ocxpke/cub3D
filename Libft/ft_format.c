/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:10:15 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:46:42 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(char specifier, va_list ap)
{
	int		count;

	count = 0;
	if (specifier == 'c')
		count += ft_p_char(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_p_str(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_p_digit(va_arg(ap, int));
	else if (specifier == 'u')
		count += ft_p_digit(va_arg(ap, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		count += ft_p_hex(va_arg(ap, unsigned int), specifier);
	else if (specifier == 'p')
		count += ft_p_point(va_arg(ap, size_t), 0);
	else
		count += write(1, &specifier, 1);
	return (count);
}
