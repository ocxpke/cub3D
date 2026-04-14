/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:56:40 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:48:11 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			count += ft_format(*(++format), ap);
		}
		else
		{
			count += write(1, format, 1);
		}
		++format;
	}
	va_end(ap);
	return (count);
}
