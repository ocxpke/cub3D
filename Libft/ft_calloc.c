/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:45:31 by romorale          #+#    #+#             */
/*   Updated: 2024/04/30 15:17:11 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*tmp;
	size_t			i;
	size_t			e;

	i = 0;
	e = num * size;
	tmp = (unsigned char *)malloc(e);
	if (!tmp)
		return (NULL);
	if (tmp)
	{
		while (i < e)
		{
			tmp[i] = 0;
			i++;
		}
	}
	return (tmp);
}
/*
int	main(void)
{
	int		size = 20;
	int		datatype = sizeof(int);
	int		spacetest = size * datatype;
	void 	*test1 = ft_calloc(size, datatype);
	void 	*test2 = calloc(size, datatype);
	int		diff = ((int) test2 - (int) test1);

	spacetest = size * datatype;
	if (test1 == NULL)
	{
		printf("error, test1 memory not allocated\n");
	}

	if (test2 == NULL)
    {
        printf("error, test2 memory not allocated\n");
    }
	
	printf("test1: %d\n", (int) test1);
	printf("test2: %d\n", (int) test2);
	printf("size: %d\n", size);
	printf("data type: %d\n", datatype);
	printf("space needed: %d\n", spacetest);
	printf("diffrence between my calloc and the real one: %d\n", diff);

	free(test1);
	free(test2);

	return (0);
}
*/
