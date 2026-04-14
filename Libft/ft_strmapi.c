/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:38:52 by romorale          #+#    #+#             */
/*   Updated: 2024/05/07 15:57:09 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str2;
	unsigned int	i;
	unsigned int	str_len;

	str_len = ft_strlen(s);
	i = 0;
	str2 = (char *)malloc(sizeof(char ) * (str_len + 1));
	if (!str2)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		str2[i] = f(i, s[i]);
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
/*
static char	ft_str_alternate_case(unsigned int i, char c)
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
    const char  string1[30] = "abcdefghijklmnopqrstuvwxyz";
	const char  string2[30] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char  string3[50] = "im crazy aaaaaaaaaaaaaaahhhhhhh!!!!";
    char        *out1  = ft_strmapi(string1, ft_str_alternate_case);
	char        *out2  = ft_strmapi(string2, ft_str_alternate_case);
	char        *out3  = ft_strmapi(string3, ft_str_alternate_case);

    printf("\nbefore: %s \n", string1);
	printf("copy after: %s \n", out1);
	printf("\nbefore: %s \n", string2);
	printf("copy after: %s \n", out2);
    printf("\nbefore: %s \n", string3);
    printf("copy after: %s \n\n", out3);
	return(0);
}
*/
