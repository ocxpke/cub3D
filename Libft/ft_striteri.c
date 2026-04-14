/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:02:52 by romorale          #+#    #+#             */
/*   Updated: 2024/05/07 18:05:03 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
/*
static char ft_str_alternate_case(unsigned int i, char c)
{
    if (i % 2 != 0)
    {
        if ((c <= 'z') && (c >= 'a'))
        {
            c = c - 32;
			return (c);
        }
		else if ((c <= 'Z') && (c >= 'A'))
        {
            c = c + 32;
            return (c);
        }
    }
    return (c);
}

int main(void)
{
    char  string1[30] = "abcdefghijklmnopqrstuvwxyz";

	printf("before: %s \n", string1);
    ft_striteri(string1, ft_str_alternate_case);
	printf("after: %s \n", string1);
    return(0);
}
*/
