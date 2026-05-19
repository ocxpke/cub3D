/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:31:30 by romorale          #+#    #+#             */
/*   Updated: 2026/05/19 15:59:12 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_path_ext2(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '.' && line[i + 1] == 'p' && line[i + 2] == 'n'
			&& line[i + 3] == 'g')
			break ;
		i++;
	}
	if (line[i] == '.' && line[i + 1] == 'p' && line[i + 2] == 'n'
		&& line[i + 3] == 'g' && line[i + 4] == '\0')
		return (1);
	else
		return (0);
}

int	check_path_ext(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '.' && line[i + 1] == 'x' && line[i + 2] == 'p'
			&& line[i + 3] == 'm')
			break ;
		i++;
	}
	if (line[i] == '.' && line[i + 1] == 'x' && line[i + 2] == 'p'
		&& line[i + 3] == 'm' && line[i + 4] == '\0')
		return (1);
	if (check_path_ext2(line))
		return (1);
	else
		return (0);
}

int	check_arg(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	i -= 1;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
		&& str[i - 3] == '.')
		return (1);
	return (0);
}

char	**get_file(char *av)
{
	int		fd;
	char	*line;
	char	*holder_map;
	char	*holder;
	char	**map;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (NULL);
	holder_map = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		holder = holder_map;
		holder_map = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	map = split_file(holder_map, '\n');
	free(holder_map);
	close(fd);
	return (map);
}

int	check_empty_file(t_dpar *game)
{
	int	i;

	i = 0;
	if (game->file_cont)
	{
		while (game->file_cont[i])
			i++;
	}
	return (i);
}
