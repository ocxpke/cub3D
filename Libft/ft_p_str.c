/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:47:21 by romorale          #+#    #+#             */
/*   Updated: 2025/07/18 18:48:24 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_p_str(char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
	{
		ft_p_char((int)*s);
		++count;
		++s;
	}
	return (count);
}
