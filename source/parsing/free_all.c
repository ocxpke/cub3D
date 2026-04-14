/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:16 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 16:28:05 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_file_cont(t_data *path)
{
	int	i;

	i = 0;
	if (path->file_cont)
	{
		while (path->file_cont[i])
		{
			free(path->file_cont[i]);
			i++;
		}
		free(path->file_cont);
	}
}

void	free_tex_col_val(t_data *path)
{
	if (path->map_s->tex_col_s->fl_col_val)
		free(path->map_s->tex_col_s->fl_col_val);
	if (path->map_s->tex_col_s->cl_col_val)
		free(path->map_s->tex_col_s->cl_col_val);
}

void	free_tex_col_paths(t_data *path)
{
	if (path->map_s->tex_col_s->no_tex)
		free(path->map_s->tex_col_s->no_tex);
	if (path->map_s->tex_col_s->so_tex)
		free(path->map_s->tex_col_s->so_tex);
	if (path->map_s->tex_col_s->we_tex)
		free(path->map_s->tex_col_s->we_tex);
	if (path->map_s->tex_col_s->ea_tex)
		free(path->map_s->tex_col_s->ea_tex);
	if (path->map_s->tex_col_s->no_tex_path)
		free(path->map_s->tex_col_s->no_tex_path);
	if (path->map_s->tex_col_s->so_tex_path)
		free(path->map_s->tex_col_s->so_tex_path);
	if (path->map_s->tex_col_s->we_tex_path)
		free(path->map_s->tex_col_s->we_tex_path);
	if (path->map_s->tex_col_s->ea_tex_path)
		free(path->map_s->tex_col_s->ea_tex_path);
	if (path->map_s->tex_col_s->fl_col)
		free(path->map_s->tex_col_s->fl_col);
	if (path->map_s->tex_col_s->cl_col)
		free(path->map_s->tex_col_s->cl_col);
}

void	free_up_to_cheklist(t_data *path)
{
	free_file_cont(path);
	if (path->checklist_s)
		free(path->checklist_s);
	free_tex_col_val(path);
	if (path->map_s->tex_col_s)
	{
		free_tex_col_paths(path);
		free(path->map_s->tex_col_s);
	}
	if (path->map_s)
		free(path->map_s);
}

void	free_map(t_data *path)
{
	int	i;

	i = 0;
	if (path->map_s)
	{
		if (path->map_s->map)
		{
			while (path->map_s->map[i])
			{
				free(path->map_s->map[i]);
				i++;
			}
			free(path->map_s->map);
		}
	}
}
