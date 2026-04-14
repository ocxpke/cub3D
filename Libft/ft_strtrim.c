/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:19:12 by romorale          #+#    #+#             */
/*   Updated: 2024/04/30 16:43:49 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s_len;
	char	*result;

	i = 0;
	s_len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != NULL && i < s_len)
	{
		i++;
	}
	while (ft_strrchr(set, s1[s_len]) != NULL && i < s_len)
	{
		s_len--;
	}
	s_len++;
	if (s1[i] == '\0')
		result = (char *)malloc(sizeof(char) * (s_len - i));
	else
		result = (char *)malloc(sizeof(char) * (s_len - i + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[i], s_len - i + 1);
	return (result);
}
/*
int	main(void)
{
	const char	string1[] = "lalalaheylalala";
	const char	string2[] = "la";
	const char  string3[] = "";
    const char  string4[] = "eee";
	char        *leftover1 = ft_strtrim(string1, string2);
	char		*leftover2 = ft_strtrim(string3, string4);

	printf("%s \n", leftover1);
	printf("%s \n", leftover2);
	return (0);
}
*/
