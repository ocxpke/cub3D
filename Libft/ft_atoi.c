/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:05:18 by romorale          #+#    #+#             */
/*   Updated: 2024/04/23 16:26:00 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ignorespace(char *c)
{
	if (*c == 32 || *c == 9 || *c == 10 || *c == 11 || *c == 12 || *c == 13)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nsign;
	int	result;

	i = 0;
	sign = 1;
	nsign = 0;
	result = 0;
	while (ignorespace((char *)&str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	while ((str[i] == '-') || (str[i] == '+'))
	{
		i++;
		nsign++;
	}
	while ((str[i]) && (str[i] >= '0') && (str[i] <= '9') && (nsign <= 1))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
int	main(void)
{
	char	str[] = "-2147483648";
	int		out;
	int		out2;

	out = ft_atoi(str);
	out2 = atoi(str);
	printf("%d", out);
	printf("\n%d", out2);
}
*/
