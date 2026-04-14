/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checklist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:02 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 15:20:55 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	count_elements(t_data *game)
{
	if ((game->checklist_s->no_tex == 1) && (game->checklist_s->so_tex == 1)
		&& (game->checklist_s->we_tex == 1) && (game->checklist_s->ea_tex == 1)
		&& (game->checklist_s->fl_col == 1) && (game->checklist_s->cl_col == 1))
		game->checklist_s->ok = 1;
	else
		game->checklist_s->ok = 0;
	return ;
}

void	check_element(t_data *game, char *line)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		game->checklist_s->no_tex += 1;
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		game->checklist_s->so_tex += 1;
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		game->checklist_s->we_tex += 1;
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		game->checklist_s->ea_tex += 1;
	if (line[0] == 'F' && line[1] == ' ')
		game->checklist_s->fl_col += 1;
	if (line[0] == 'C' && line[1] == ' ')
		game->checklist_s->cl_col += 1;
	else
		return ;
}

int	check_element_name(char *s)
{
	if (!s)
		return (0);
	if ((s[0] == 'N' && s[1] == 'O') || (s[0] == 'S' && s[1] == 'O')
		|| (s[0] == 'W' && s[1] == 'E') || (s[0] == 'E' && s[1] == 'A' ))
	{
		if (s[2] == ' ' && s[3] != '\0')
			return (1);
		else
			return (0);
	}
	else if (s[0] == 'F' || s[0] == 'C')
	{
		if (s[1] == ' ' && s[2] != '\0')
			return (1);
		else
			return (0);
	}
	else
		return (1);
}

int	file_checklist(t_data *game)
{
	int	j;

	j = 0;
	while (game->file_cont[j])
	{
		if (!check_element_name(game->file_cont[j]))
			return (0);
		j++;
	}
	j = 0;
	while (game->file_cont[j])
	{
		check_element(game, game->file_cont[j]);
		j++;
	}
	count_elements(game);
	if (game->checklist_s->ok)
		return (1);
	else
		return (0);
}
